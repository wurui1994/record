import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URLConnection;
import java.net.URL;

public class request {
	public static void webRequest(String strURL) {
		String temp;
		try {
			URL url = new URL(strURL);
			URLConnection conn = url.openConnection();
			InputStreamReader isr = new InputStreamReader(conn.getInputStream());
			BufferedReader br = new BufferedReader(isr);
			while ((temp = br.readLine()) != null) {
				System.out.println(temp);
			}
			br.close();
			isr.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		webRequest("http://www.baidu.com");
	}
}