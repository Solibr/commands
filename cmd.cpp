mkdir myFolder // создание папки с именем myFolder
md myFolder  // то же самое

rmdir myFolder // удаление папки с именем myFolder
rd myFolder // то же самое
	/s  // рекурсивно

tasklist // список процессов

taskkill { // завершить процесс
	taskkill /PID 20765 // заершить процеесс с id = 20765
	taskkill /IM explorer.exe // завершить процесс по имени
	taskkill /IM explorer.exe /F // принудительно 
}

=== Utils ===

dxdiag
ipconfig
ping <ip> { // проверить доступность ip 
	ping -a <ip> // больше информации + есть имя компьютера
}
tracert <ip> // рассировка маршрута, показывает имя компьютера
arp -a // показывает ip всех членов локальной сети
whoami // показывает текущее имя пользователя
hostname // показывает имя текущего компьютера
netstat { // занятые порты
	-a // показать все
	-b // показать имя процесса
	-o // показать порт
}

curl /* сделать http запрос*/ {
	
	// Пример
	curl www.google.com
	
	// Примеры
	curl -H Content-Type:application/json -d "{\"email\":\"artem.gaschev2013@yandex.ru\"}" http://localhost:8080/api/v1/auth/password/recovery/
	curl -H "Content-Type: application/json" -d "{\"email\":\"artem.gaschev2013@yandex.ru\"}" http://localhost:8080/api/v1/auth/password/recovery/
	
	-I // Вывести заголовки ответа
	-H // Указать заголовок запроса
	-d { // передать данные (при этом метод изменится на POST)
		Указать данные можно как в стиле query string, так и json
		"user=someUser&email=someEmail"
		"{\"user\":\"someUser\",\"email\":\"someEmail\"}"
		// json требует указания двойных кавычек. В cmd их нужно экранировать через \ 
	}
	-X // указать метод
	
	// Примеры
	curl -H Content-Type:application/json -d "{\"email\":\"artem.gaschev2013@yandex.ru\"}" http://localhost:8080/api/v1/auth/password/recovery/
	curl -H "Content-Type: application/json" -d "{\"email\":\"artem.gaschev2013@yandex.ru\"}" http://localhost:8080/api/v1/auth/password/recovery/
	
	Как обычно, если после ключа значение указывается без пробелов, то кавычками обрамлять не обязательно
}

