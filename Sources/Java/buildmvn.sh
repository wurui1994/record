mvn archetype:generate -DgroupId=demo -DartifactId=Console -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false -DarchetypeCatalog=local
cd Console
# mvn compile
# mvn exec:java -Dexec.mainClass="demo.App" -q
mvn clean compile exec:java -Dexec.mainClass="demo.App" -q