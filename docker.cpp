Тесты {
	Есть команды:
	docker run --rm --name skill-redis -p 127.0.0.1:6379:6379/tcp -d redis
	docker exec -it skill-redis redis-cli
	
	Надо понять как рабоатет exec
	- Попрпобовать создать контейнер. {
		- Как есть
		- Создать с другими ключами, -it вместо -d
	}
	- Попробовать зайти в redis-cli {
		- как есть
		- зайти другим путём: {
// Заходим сначала в консоль
docker exec -it skill-redis bash 
// Внутри из консоли запустить клиент Redis
redis-cli
		}
		Проверить, будет ли это тоже самое, или будет выглядеть и работать иначе
			
	}
	
}


Basic commands to use containers {
DOCKER // вывод подсказки
DOCKER IMAGES // вывод списка образов
DOCKER PS // вывод списка запущенных контейнеров
DOCKER PS -a // вывод всех контейнеров
DOCKER RM containerId // удаление кнтейнера
DOCKER RMI imageId { // удаление образа 
	DOCKER IMAGE RM imageId // возможно синоним
}

DOCKER RUN imageName { // создание и запуск контейнера. 
	-it  { // DOCKER RUN -it imageName  // --IT - создание и запуск контейнера в интерактивном режиме. То есть в терминале произойдёт переход в приложение 
		// Пример
		docker run -it python // тут интерактивно запустится питон и мы попадём в консоль ввода кода питона
		
		Ctrl + D  // выйти из интерактивного режима, вернуться в cmd
	}
	--rm // автоматически удалить контейнер после выхода из него. удобно для тестов, когда нужно проверить как себя поведёт контейнер при тех или иных параметрах запуска
	-p 80:8080 // specify ports		outer:inner
	--name someName // DOCKER RUN --NAME MyContainer imageName // --NAME - указать имя создаваемому контейнеру
	-d // detach console from container. By default it's attached, and if you will exit the container it will stopped. Detached containers will live while you woun't stop them, or docker daemon is alive
	
	Example {
		DOCKER RUN -p outerPost:innerPort --name containerName -d imageName { // совместить порты на устройстве и внутри контейнера 
			docker run -p 8080:8001 MyImage
		}
	}
}

DOCKER START containerName // запуск созданного ранее контейнера
DOCKER STOP containerName // остановка контейнера
DOCKER KILL containerName // аварийная остановка контейнера, например, если контейнер перестал отвечать
	
}

Dockerfile, and making containers {
Dockerfile {


	FROM imageName:version			// какой образ исползовать как основу
	COPY myProjectSourceDir myProjectDestDir  	// какие файлы из текущей папки копируем в какую папку внутри контейнера
	WORKDIR workDir			// аналог cd в bash
	EXPOSE port				// указывается порт для приложения
	RUN command words		// выполнить действие при первоначальном запуск контейнера
	CMD ["word1", "word2"] 	// выполнение действия при каждом запуске контейнера
	
	// Пример
	FROM openjdk:11			
	COPY . /usr/src/myapp  	// тут мы указали, что из той папки, где производится docker build все файлы копируются в /usr/src/myapp внутри контейнера
	WORKDIR /usr/src/myapp // переходим в эту папку
	EXPOSE 8001	// объявить какие порты прослушивает приложение. не обязательно, так как параметр -p переопределит эти порты. Может пригодиться при использовании -P, но я сам не знаю как этим пользоваться
	RUN javac Main.java
	CMD ["java", "Main"]
	
	подробнее о CMD {
		В примере видим следующее:
			CMD ["java", "Main"]
		Это говорит докеру, что нужно сконструировать команду в консоли подставив слова из массива по очереди через пробел
		То есть массив строк ["java", "Main"] будет преобразован в команду java Main, которая запускает java класс
	}
}

DOCKER BUILD pathToDockerfile { // построить проект, указав путь к докерфайлу. Путь указывается относительно текущего положения 
	Dockerfile shoud be in project directory
	
	Можно указать точку, если мы находися в этой же директории:
	Пример:
		docker build .
		
	-t imageName // to name an image
	
	Пример:
		DOCKER BUILD -t image-title pathToDockerfile // такми образом можно назвать образ. Верхний регистр недопустим
}
	
}

Other commands {
DOCKER tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG] // создаёт копию образа с другим названием. По сути переименование, но с сохренением старого образа.
DOCKER rename CONTAINER NEW_NAME // переименовать контейнер

DOCKER login // логин - требуется для отправки образа в репозиторий

DOCKER PUSH imageName { // загрузить образ в репозиторий
	у образа должно быть особое название: аккаунт/имя
	например, artem-gashev/my-application
}
DOCKER PULL imageName { // скачать образ из репозитория
	// скачать образ из репозитория
	DOCKER PULL imageName:versionNumber // определить версию скачивемого образа. 
	// Например:
	docker pull openjdk:8

	// Если версия не указана, то это аналогично следующему вызову:
	DOCKER PULL imageName:LATEST
	
}


DOCKER container logs containerName { // показать логи запущенного контейнера
	-f // DOCKER container logs -f containerName // остаться в логах (как если бы мы запустили контейнер с -it параметрами)
	--since timeStamp // от 
	--until timestamp // до
}


DOCKER COMMIT containerName newImageName // сохранение состояния контейнра в image

DOCKER SAVE -o fileName imageName // сохранить образ как файл
DOCKER LOAD -i fileName // подгрузить образ из файла

DOCKER NETWORK {
	
	Связь контейнеров и внешней системы {
		Из системы внутрь контейнера {
			через настройку портов при команде run -p outerPort:innerPort
		}
		Из контейнера в контейнер {
			Организовать сеть контейнеров.
			приложение может обратиться по ip адресу в сети Docker или по названию контейнера
			
			Контейнер может быть одновременно в нескольких сетях Docker.
		}
		Из контейнера во внешнюю систему {
			вместо ip:port прописать host.docker.internal:outerPort
		}
		
		Более подробно {
			Возможные положения:
			- bridge
			- none
			- своя сеть
			- host (docker net) // работат, кажется только на linux
			- jar // host (not in docker)
			
			Возможные способы обращения:
			- localhost
			- по имени контейнера или по ip (равнозначно (кроме случая с сетью bridge))
			- host.docker.internal // то есть на внешнее устройство
			
			Тесты {
				+ docker-net -> docker-net: container_name, ip
				
				+ jar -> docker-net 	: localhost
				+ docker-net -> jar		: host.docker.internal
				
				+ bridge -> docker-net : host.docker.internal
				+ docker-net -> bridge : host.docker.internal
				+ bridge -> bridge     : ip контейнера (по имени не сработает) или host.docker.internal
				
				+ none -> docker-net	: нет доступа (не происходит expose портов. Нельзя подключиться внутри докера)
				+ docker-net -> none	: нет доступа (то же)
				
				+ another-net -> docker-net: host.docker.internal
				
				// linux. На windows сеть host не работает
				+ jar -> host : localhost
				+ host -> jar : localhost
			
				+ docker-net -> host	: host.docker.internal, but also need next option for container run: --add-host host.docker.internal:host-gateway
			}
			
		}
	}
	
	DOCKER NETWORK CREATE my-net // создание
	DOCKER NETWORK remove my-net // удаление 
	DOCKER NETWORK ls // список сетей
	DOCKER NETWORK INSPECT networkName { // информация о сети
		DOCKER INSPECT networkName // укороченный синоним
	}
	DOCKER NETWORK CONNECT my-net my-postgres // присоединение контейнера
	DOCKER RUN --NETWORK networkName imageName // запуск контейнера сразу в сети
		
}

DOCKER EXEC {
	docker exec -it skill-redis redis-cli 	// вход в приложение redis-cli внутри контейнера skill-redis
	docker exec -it front bash 				// вход в консоль bash внутри контейнера front
	
}

DOCKER cp containerName:/source/path dest/path { // копирование данных между хостом и контейнером
	Из контейнера
	DOCKER cp containerName:/source/path dest/path
	
	В контейнер
	DOCKER cp /source/path containerName:/dest/path
}

docker context {
	/* С помощью docker CLI можно обращаться к разным экземплярам docker:
		- defalft
		- desktop
		- возможно какой-то remote экземпляр
	*/
	
	docker context ls // список доступных контекстов (куда будут применяться команды)
	docker context use default // пример переключения контекста на defalt
}	
}



