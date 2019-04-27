extern crate hyper;
extern crate hyper_native_tls;

use hyper::Client;
use hyper::net::HttpsConnector;
use hyper_native_tls::NativeTlsClient;
use std::io::Read;

fn main() {
    let ssl = NativeTlsClient::new().unwrap();
    let connector = HttpsConnector::new(ssl);
    let client = Client::with_connector(connector);

    let mut resp = client.get("https://www.baidu.com").send().unwrap();
    let mut body = vec![];
    resp.read_to_end(&mut body).unwrap();
    println!("{}", String::from_utf8_lossy(&body));
}