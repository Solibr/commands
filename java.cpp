javac fileName.java // скомпилировать java файл. Получим файл с расширением class
	-d // куда сохранить классы - в отдельную папку. По умолчанию создаются радом с каждым java файлом
	-classpath yourClasspath //  указать classpath
	-cp yourClasspath // короткий синоним -classpath
	
	
jar cfe My.jar main.Main main/Main.class
	c // флаг - create чтоб создать jar
	f // указать имя файла (My.jar)
	e // указать entrypoint (main.Main) 
	// далее идёт перечисление классов для упаковки (main/Main.class)
	// Пример: jar cfe My.jar main.Main main/Main.class some/Some.class another/package/Foo.class
	
java fileName {// исполнить полученный класс-файл. Расширение в имени не указывается
	-jar { // execute jar
		java -jar jarName.jar // выполнить джава архив
		java -jar jarName.jar arg anotherArg // выполнить джава архив передав 2 аргумента в main(String[] args);
		java -jar jarName.jar --propertyName=value { // это тоже передача парметров, но spring при использовании -- интерпретирует их по своему
			Пример:
			java -jar myApp.jar --server.port=8081
			java -jar app.jar --name="Spring" // override property "name" with "Spring" value
			java -jar myproject.jar --spring.config.name=myproject { // specify properties filename
				/*
				if we have file named some.properties
				and we don't want to use "application" prefix
				we can specify it.
				Note, that we shoudn't write anything afrer "."
				*/
				--spring.config.name=some // ok
				--spring.config.name=some.properties // will not work

			}
			java -jar myApp.jar --spring.profiles.active=someProfile // особенный случай. Устанавливает название профиля, которое влияет на то, какой файл свойств будет использован поверх дефолтного и какие бины будут добавлены в контекст
		}

	}
	-D { // установить системную переменную
		-Djava.library.path=.  // указать библиотеку 
		
		Для более широкого понимания. Данные записи приводят к одному и тому же результату
		java -jar app.jar --spring.profiles.active=test
		java -Dspring.profiles.active=test -jar app.jar
		При этом порядок аргументов имеет значение
		
		Несмотря на то, что результат одинаковый, суть разная - 
		У напрямую переданного параметра больший приоритет, чем у системной переменной
	}
	
}

nohup java -jar /web/server.jar & // запуск в фоне

jps.exe { // Показывает id процессов на java (располагается в java/bin)
	jps { 
		-l // покажет исполняемые классы 
		-v // покажет больше всякого
	}
}

jstack PID // где PID - process id. Покажет stackstace потоков

javadoc {
	
	-d <path> // where to put documentation
	--sourcepath <path> // path to source files
	-subpackages <package> // defines package where javadoc will recursively seek for sourcefiles
	
	Example
	javadoc -d docs --source-path src -subpackages all // at this example there is package named "all" which contains inner packages
	
	
}