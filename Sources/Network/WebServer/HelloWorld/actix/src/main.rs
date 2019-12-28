// use actix_web::{get, middleware, App, HttpServer};
use actix_web::{get, App, HttpServer};

#[get("/")]
async fn no_params() -> &'static str {
    "Hello world!\r\n"
}

#[actix_rt::main]
async fn main() -> std::io::Result<()> {
	// println!{"{} {}", num_cpus::get(), num_cpus::get_physical()}
    HttpServer::new(|| {
        App::new()
            // .wrap(middleware::DefaultHeaders::new().header("X-Version", "0.2"))
            // .wrap(middleware::Compress::default())
            // .wrap(middleware::Logger::default())
            .service(no_params)
    })
    .bind("127.0.0.1:8000")?
    .workers(num_cpus::get_physical())
    .run()
    .await
}
