// создание Maven проекта в пустой папке

Generate project {
	Синтаксис
	mvn archetype:generate 
	
	-DgroupID=myGroupID 
	-DartifactID=myArtifactID 
	-DinteractiveMode=true		// в интерактивном режиме можно выбрать арехетип для построения проекта и ещё кое-что
	

	
	Пример (С использованием wrapper)
	./mvnw archetype:generate -DgroupId=ru.arvoglade.example -DartifactId=mavenTest
	
	Пример (С использованием wrapper)(Без интерактивного режима, чтобы сделать стандартный мавеновский архетип)
	./mvnw archetype:generate -DgroupId=ru.arvoglade.example -DartifactId=mavenTest -DinteractiveMode=false
}



// сборка проекта. В результате появляется папке target
mvn compile // данную команду можно ввести как в cmd, так и в терминале IDEA

// упаковка проекта в war файл
mvn package war:war


== 

использование утилиты mvnw

На Windows можно использовать так
./mvnw.cmd clean package // в данном случае выполнится сразу 2 цели последовательно: clean и package