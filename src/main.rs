extern crate clap;
extern crate handlebars;
#[macro_use]
extern crate rust_embed;

use std::env;
use std::format;
use std::fs;
use std::fs::File;
use std::io::prelude::*;
use std::io::{Error, ErrorKind};
use std::path::Path;
use std::process;

use clap::{Arg, Command};
use handlebars::Handlebars;
use serde::Serialize;

#[derive(Serialize)]
struct Context {
    pass_name: String,
    pass_kind: String,
    dest_dir: String,
}

#[derive(RustEmbed)]
#[folder = "src/templates/"]
struct Templates;

fn template(name: &str) -> String {
    let file_bytes = Templates::get(name).unwrap();

    String::from_utf8(file_bytes.data.to_vec()).unwrap()
}

fn build_pass(ctx: &Context) -> Result<(), Error> {
    let reg = Handlebars::new();

    let pass_path = Path::new(&ctx.dest_dir).join(&ctx.pass_name);
    fs::create_dir(&pass_path)?;
    fs::create_dir(&pass_path.join("build"))?;

    File::create(pass_path.join(".clang-format"))
        .and_then(|mut file| file.write_all(&template("common/.clang-format").as_bytes()))?;

    let cmakelists = reg
        .render_template(&template("common/CMakeLists.txt"), ctx)
        .unwrap();
    File::create(pass_path.join("CMakeLists.txt"))
        .and_then(|mut file| file.write_all(cmakelists.as_bytes()))?;

    let pass_src = reg
        .render_template(&template(&format!("{}/pass.cpp", ctx.pass_kind)), ctx)
        .unwrap();
    File::create(pass_path.join(format!("{}.cpp", ctx.pass_name)))
        .and_then(|mut file| file.write_all(pass_src.as_bytes()))?;
    Ok(())
}

fn run() -> Result<(), Error> {
    let current_dir = env::current_dir()?;
    let current_dir_str = current_dir
        .to_str()
        .ok_or(Error::new(ErrorKind::Other, ""))?;

    let matches = Command::new(env!("CARGO_PKG_NAME"))
        .version(env!("CARGO_PKG_VERSION"))
        .about(env!("CARGO_PKG_DESCRIPTION"))
        .arg(
            Arg::new("kind")
                .help("sets the pass kind")
                .short('k')
                .long("kind")
                .multiple_occurrences(false)
                .possible_values(&["module", "function", "block", "loop"])
                .default_value("function"),
        )
        .arg(
            Arg::new("dest")
                .help("sets the output directory")
                .short('d')
                .long("dest")
                .multiple_occurrences(false)
                .default_value(current_dir_str),
        )
        .arg(
            Arg::new("name")
                .help("the name of the pass")
                .index(1)
                .required(true),
        )
        .get_matches();

    let ctx = Context {
        pass_name: matches.value_of("name").unwrap().to_string(),
        pass_kind: matches.value_of("kind").unwrap().to_string(),
        dest_dir: matches.value_of("dest").unwrap().to_string(),
    };

    build_pass(&ctx)?;

    Ok(())
}

fn main() {
    // NOTE(ww): Returning a Result from main doesn't produce a nice error; wrap run() instead.
    process::exit(match run() {
        Ok(()) => 0,
        Err(e) => {
            eprintln!("Fatal: {}", e);
            1
        }
    });
}
