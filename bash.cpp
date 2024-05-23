
!! ПРИБРАТЬСЯ В ЭТОМ ФАЙЛЕ {
	На данный момент соержимое достаточно плоско сапределено. 
	Необходимо углубить структуру, добавить разделы
	+ Возможные разделы {
		- некоторая база {
			clear, whoami
		}
		- навигация работа с файловой системой { cd, pwd, rm, cp, rp, mount(umount) }
		- скрипты
		- сеть {
			ssh, scp, ip ...
		}
		- users, groups, permissions
		
		Что делать с некоторыми утилитами не совсем понятно. 
		Наверное лучше всего встраивать их в соответсвующий назначению раздел.
		Например vim нужно разместить в разделе "работа с фйловой системой", 
		и где-то там создать раздел с утилитами, такими как vim, touch и что-то ещё
	}
	- прибраться внутри разделов

}

Base {
	clear // очистить экран

	uname -a // имя компьютера
	
	apt {
		apt update // обновить информацию о доступных пакетах
		apt install package-name // установить пакет
		apt install package-one package-two // утсновить несколько пакетов
		apt install package-name -y // -y чтобы не спрашвать подтверждения
		apt remove package-name // удаление покета
	}

ps // список процессов
ps -eF {// 
	e больше процессов
	F больше инфы
}
top // список процессов покрасивее
htop// список процессов покрасивее и цветастый
kill 51355 // завершить процесс где id = 51355



}
Environment variables {
	// list
	env 
	
	// print one with name
	printenv VARIABLE_NAME
	echo $varname
	
	// set env var for current session
	export VARIABLE_NAME=value
	
	// to persist env var edit next file
	~/.bashrc 
	// add env var in this file
	export VARIABLE_NAME=value
	// and make changes take effect
	source .bashrc
}
Navigation and file system {
	cd myDirrectory/myFolder { // сменить директорию
		cd / // вернуться в начальную дирректорию
		cd ~ // перейти в дирректорию текущего юзера
		cd ./.. // вернуться вверх на один каталог
		cd ./../.. // вернуться на 2 каталога ...
		cd someDir // команда ищет дирректорию для перехода только в текущем каталоге
		cd /someDir // команда ищет дирректорию для перехода начиная с корневого каталога
		pwd // показать в какой диррекотрии я нахожусь
	}
	pushd /Documents // переход в дирректорию с возможностью возврата
	popd // возврат в директорию

	ls // показать содержимаое текущего каталога
		ls -a // показать все (скрытые элементы тоже)
	ll // показать содержимое текущего каталока, но со всякими приколюхами ?
	
	dir // тоже самое
	
	du -sh /directory	// показать размер директории

	mkdir myFolder // создание папки с именем myFolder

	rmdir myFolder // удаление папки с именем myFolder
		- r { // рекурсивно // по факту не всегда работает
			Запасной вариант:
			rm -rf myFolder
		}
		- f // принудительно

	touch fileName.txt // создать файл

	cat { // простое управление контентом файлов
		cat file.txt // вывести содержимое файла в консоль
		cat file.txt > file2.txt // заменить содержимое файла 2 содержанием файла 1 (> оператор просто перенаправляет вывод)
		cat file.txt file3.txt > file2.txt // заменить содержимое файла 2 склеенным содержанием файла 1 и файла 3(> оператор просто перенаправляет вывод)
		cat file.txt >> file2.txt // дописать в файл 2 содержанием файла 1
		cat > file.txt // записать в файл следующие симоволы (перед оепратором > ничего не стоит, поэтому в файл перенаправится стандартный ввод)
			Ctrl + d // завершить ввод (передать сигнал о конце файла)
	}
	
	less {
		print content of the file by lines
		less text.txt
	}

	grep {
		finds and prints lines that contain strings passed as argument
		cat text.txt | grep some_word
	}

	cp source destination // копирование



	Vim {
		2 режима: командный и режим ввода текста
		
		i // переход в режим ввода текста
		
		Ctrl + c или Esc // выход в прошлое меню. Возвращает из меню ввода текста в командное меню
		Shift + Z -> Shift + Z // (дважды) выход из редактора
		:q // выход из редактора
		:w // принудительное сохранение
		
		Навигация
		h, j, k, l // <-h		jv 		k^ 		l-> // движение в стороны
		e, b // перемещение по словам
		
		x // удаление символа
		d -> d // dd удаление строки
		u // откатить изменения
		
	}


===============
}
Scripts {
	
	// Тут у нас одно и то же. Нужно удалить лишнее по потеряв нужное

	BASH SCRIPT {
		Example:
			#!/bin/bash
			java -jar ~/Games/TLauncher-2.879.jar
			$SHELL
		Explanation:
			#!/bin/bash // points which programm to use for run script
			java -jar ~/Games/TLauncher-2.879.jar// is your script
			$SHELL // needs if you don't want console to be closed

	}

}
Net {
	ssh {
	apt install openssh-server // установить
	
	service ssh status // статус
	service ssh start // запуск
	service ssh restart // перезапуск
	
	ssh -i fileWherePriveteKeyStored 192.168.1.100 // подключиться к указанному ip используя определённый ключ
	ssh 192.168.1.100 // подключиться к указанному ip по ключю, который называется id_rsa
	ssh username@192.168.1.100 // подключиться к ip как определённый юзер
	
	-p // use specific port, differs from 22
	
	ssh-keygen // сгенерировать ключи
		они будут в папке root/user/.ssh/
	
	предоставление доступа к компьютеру по ключу {
		в user/.ssh/ нужно создать файл authorized_keys, в который нужно добавить публичный ключ
		
		рекомендуется исправить права доступа к authorized_keys
		chmod 0600 authorized_keys		
	}
	предоставление доступа к root по паролю {
		1. установить пароль
			passwd root
		
		2. разрешить вход в root пользователя
			в etc/ssh изменить sshd_config:
				установить 
					PermitRootLogin yes
	}
	
	
	exit // закрыть соединение
}

scp { // передача файлов по сети

	// от себя на удалённый
	scp /home/test.txt root@123.123.123.123:/directory
	
	// с удалённого к себе
	scp root@123.123.123.123:/home/test.txt /directory
	
	- r // рекурсивно все подпапки и файлы
	scp -r root@123.123.123.123:/home/dir /directory
	
	-P // указать порт, если он не 22
}

ip -br a // узнать свой ip
	установка утилиты ip apt install iproute2

netstat -ntlp // используемые порты
	apt install net-tools


}
Users, groups, permissions {

	whoami // вывести текущее имя пользователя
	w // узнать кто подключён к текущему компьютеру

	Users {
		cat etc/passwd // получить список всех юзеров 
		useradd petya { // добавить юзера petya 
			--create-home {// создаёт домашнюю директорию для нового юзера
				По сути этого достаточно, чтобы создать нормально обычного юзера
				-m // синоним
			}
			Сделать юзеру нормальный терминал {
				// When arrow keys don't work as they should, and path is not shown
				
				chsh -s /bin/bash // сам себе юзер сделать может
				sudo chsh -s /bin/bash <username> // можно сделать дургому юзеру, если у тебя есть права
				
				// Cause of this problem is when new user account was created with /bin/sh as its login shell (which symlinks to the dash shell by default) instead of /bin/bash
				
				https://askubuntu.com/questions/325807/arrow-keys-home-end-tab-complete-keys-not-working-in-shell
			}
		}
		userdel petya // удалить
		passwd petya //  изменить пароль
		su username // переключиться на другого юзера
		adduser username sudo // adds a user to the sudo group
		list users {
			cat /etc/passwd 	// list all users (system and regular users)
			getent passwd 		// same
			
			// get information about max and min ID number for  system and regular users
			cat /etc/login.defs | grep UID 	// from 1000 to 60000 for regular users
			
			getent passwd {1000..60000}		// list all regular users
		}
	}

	Groups {
		// добавить юзера в группу sudo
		sudo usermod -aG sudo <username>
		
		groups // посмотреть, в каких группах состоит текущий пользователь
	}

	Permissions {

		Синтаксис
		chmod u+w filename { 
			// где на месте "u" - кому устанавливаем права: u - юзер(владелец), g - группа, o - остальные
			// "+" добавление права, "-"отнятие права
			// на месте "w" тип права: r - read, w - write, x - execute
			
			Примеры:
			chmod o-r filename // отнять право на чтение файла остальным юзерам
			chmod ug+wx filename // дать право юзеру(владельцу) и группе на запись и выполнение файла
			chmod +x some-script.sh // дать всем право доступа на исполнение скрипта
			
		}
		
		-R { // рекурсивно
			Пример:
			chmod -R +x some-folder // Даёт право на исполнение в этой папке всех внутренних файлов всем пользователям
		}
		
		Дополнительный синтаксис 
		chmod 666 filename {
			//если нужно за раз изменить много прав по-разному, например:
			chmod u+rwx,g+rw,o+r
			// хотя это можно немного по другому записать, но особо не сократить:
			chmod ugo+r,ug+rw,u+x
			
			В данном случае можно использовать числовой формат задания прав
			chmod nkf filename { где
				n - права для владельца
				k - права для группы
				f - права для остальных
				и каждое из них число от 0 до 7, которое опредяется как сумма прав:
				1 - исполнение
				2 - запись
				4 - чтение
				
				Примеры:
				chmod 777 filename // все могут делать всё
				chmod 000 filename // никто не может делать ничего
				chmod 764 filename // владелец всё, группа не может только исполнять, а остальные могут только читать
				chmod 751 filename // владелец всё, группа читать и исполнять, остальные только исполнять
				chmod 0600 filename // только владелец может только читать и писать. Остальные не могут ничего, первый ноль игнорируется, как если бы это было числом
			}
			
			

		}
		
	}

}

Utils {
	screen { // многозадачность в терминале
		apt get screen
		
		screen {// запустить приложение и войти в сессию
			screen -S session-name // указать имя сессии
			screen -ls // список сессий. Вывод: id процесса, имя сессии
			kill process-number // закрыть сессию (как и любое другое приложение)
			screen -r session-name // подключиться к сессии по имени
			screen -r process-number // подключиться к сессии по id
		}
		Формат записи {
			^a  // Одновременное нажатие Ctrl + a. Это основная комбинация управления screen
			^a c // (последовательно ^a, потом с)
		}
		Внутри сессии {
			^a ? // подсказка
			
			^a c // создать окно
			^a w // список окон
			^a 1 // перейти на 1 окно
			^a 2 // перейти на 2 окно
			...
			^a " // ввести номер окна, на которое перейти
			^a n // следующее окно
			^a p // предыдущее окно

			^a A // переименовать окно
			
			^a k // закрыть окно
			^a d // выйти из screen (сессия с окнами сохранится)
			^a \ // выйти из screen (сессия с окнами закроется)
		}
		Разделённые экраны {
			^a S // разделить по горизонтали
			^a | // разделить по вертикали
			^a Tab // переключение между экранами
			^a X // скрытие текущего экрана
			^a Q // оставить только текущий экран
			
			В экранах можно открывать окна терминала
			^a c // новые окна
			^a 1 // (...) существующие
		}
	}

}

