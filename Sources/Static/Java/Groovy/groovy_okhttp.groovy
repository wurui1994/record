// groovy.grape.Grape.grab(group:'com.squareup.okhttp', module:'okhttp', version:'2.7.5')
@Grab(group='com.squareup.okhttp', module='okhttp', version='latest.release')
import com.squareup.okhttp.*;

url="https://www.cnblogs.com";
client = new OkHttpClient();
request = new Request.Builder().url(url).build();
response = client.newCall(request).execute();
println response.body().string();