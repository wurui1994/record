extern crate reqwest;

fn main() {
    println!("GET https://www.baidu.com/");

    let mut res = reqwest::get("https://www.baidu.com/").unwrap();

    println!("Status: {}", res.status());
    println!("Headers:\n{:?}", res.headers());

    // copy the response body directly to stdout
    std::io::copy(&mut res, &mut std::io::stdout()).unwrap();

    println!("\n\nDone.");
}
