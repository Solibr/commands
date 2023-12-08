
MySQL commands {
	// Регистр не важен. В описании регистр применяется для удобства
	general {
		
		// Команды применяемые извне MySQL по отношению к базе данных.
		
			//Вход
			mysql -u root -p // для запуска MySQL. Далее нужно ввести пароль.
			mysql -u root -p pasword //  есть и такой вариант. Сразу пишется пароль.
			
			// Импорт дампа
			mysql -u root -p database_name < путь_до_дампа// для загрузки дампа. База данных должна уже существовать
			
			// Создание дампа
			mysqldump -uroot -ppassword database_name > путь_до_дампа // выгрузка дампа в файл.
		
		// Команды применяемые внутри MySQL
		quit // выход из базы данных
		exit // также выход из базы данных
	}
	
	Типы данных {
		INT
		VARCHAR
		VARCHAR(20)
		...
	}
	
	DATABASES {
		SHOW DATABASES; // Показыввает базы данных
		CREATE DATABASE <database name>; // создать базу данных
		CREATE DATABASE [IF NOT EXISTS] имя_базы_даных
		CREATE DATABASE IF NOT EXISTS Skillbox // форма команды, которая создаёт базу, если её ещё нет.
		
		DROP DATABASE имя_базы_даных; // удаление базы данных
		
		DROP DATABASE [IF EXISTS] имя_базы_даных;
		
		USE DATABASE <database name> // переключение на другую базу
	
	}
		
	TABLES {
		SHOW TABLES; // показать ссписок таблиц в БД
		
		CREATE {
			CREATE TABLE название_таблицы
			(название_столбца1 тип_данных атрибуты_столбца1, 
			 название_столбца2 тип_данных атрибуты_столбца2,
			 ..............................
			 название_столбцаN тип_данных атрибуты_столбцаN,
			 атрибуты_уровня_таблицы
			)
			
			// пример
			CREATE TABLE Customers 
			(
				Id INT,
				Age INT,
				FirstName VARCHAR(20),
				LastName VARCHAR(20)
			);
		}
		
		DESCRIBE table_name; // выводит информацию о полях таблицы и их свойствах
		
		DESCRIBE table_name\G // выводит информацию о полях таблицы и их свойствах
		
		RENAME TABLE старое_название TO новое_название; // переименование таблицы
		RENAME TABLE Customers TO Clients;
		
		TRUNCATE TABLE Clients; // удалание данных в таблице
		TRUNCATE Clients;       // так тоже должно работать
		
		DROP TABLE Clients; // удаление таблицы
		
		ALTER TABLE table_name ADD COLUMN field_name тип_даных; // добавить столбец в таблицу
		
		ALTER TABLE table_name RENAME COLUMN old_name TO new_name; // изменить название таблицы.
		
		ALTER TABLE tableName DROP COLUMN columnName; // удаление
	}
	
	SELECT {
		
		mysql -uroot -ppassword -e "USE my_database; set names utf8mb4; select * from table" > file_name.txt // Так можно выгрузить данные в файл. Однако в моих тестах требовалось прописывать set names как в примере, так как без него были проблемы с кодировкой. Видимо потому что Windows по-умолчанию использует что-то традиционое
		
		Базовые выражения {
			
			// SELECT FROM
			SELECT * FROM table_name; // * - обозначает вывод всех полей из таблицы
			SELECT field FROM table_name; // вывод конткретного поля из таблицы
			SELECT field_1, field_2 FROM table_name; // вывод нескольких полей из таблицы
			
			// WHERE
			SELECT * FROM table_name WHERE <условие>;
			SELECT * FROM table_name WHERE <условие> AND <условие>; // условий может быть больше
			SELECT * FROM teachers WHERE age < 30;
			SELECT * FROM teachers WHERE age < 30 AND salary < 5000;

			// ORDER BY
			SELECT * FROM teachers ORDER BY age; // вывод всех учителей из таблицы в порядке возрастания их возраста.
			SELECT * FROM teachers WHERE age < 30 ORDER BY age; // то же самое, но только тех, кто моложе 30
			SELECT * FROM teachers WHERE age < 30 ORDER BY age DESC; // DESC от слова descending - убывающий. Т.е. обратный порядок
			SELECT * FROM teachers ORDER BY age DESC, salary; // Сортировка по двум параметрам. Если будет 2 и более человека с одним возрастом, то они относительно друг друга будут отсортированы по зарплате. У отдельных колонок по которым сортируем можем написать DESC
			
			// LIMIT
			SELECT * FROM teachers WHERE age < 30 AND type = 'programming' ORDER BY age DESC, salary LIMIT 3; // LIMIT - ограничивает количество строк в выдаче - только первые 3 строки
		}
		//------------	
		SELECT DISTINCT field_name FROM table_name; // Для исключения повторяющихся результатов.
		SELECT DISTINCT type FROM courses;
		
		UNION {
			<запрос> UNION <запрос>; /*Объединение результатов двух запросов. 
			Особенности: 
				- должно быть одинаковое количесто запрашиваемых полей
				- условия могут быть у каждого свои и они не пересекаются
				- может быть только один LIMIT на оба выражния
				- выборка будет отсортирована
				
			*/
			SELECT name FROM teachers WHERE salary < 5000 UNION SELECT age FROM students WHERE age < 20 LIMIT 100;
			
			// Можно писать в одну строку, как выше, а можно переносить строки:
			SELECT name FROM teachers WHERE salary < 5000
			UNION
			SELECT age FROM students WHERE age < 20 LIMIT 100;
			
			/* UNION по умолчанию исключает одинаковые результаты из выборки. Т.е. одинаковых результатов не будет даже среди результатов отдельных запросов
			UNION ALL не делат исключения*/
			SELECT age FROM teachers WHERE age < 25
			UNION ALL
			SELECT age FROM students WHERE age < 20;
			
			// Можно исключить повторяющиеся результаты внутри запросов, но обединить их без исключения. В таком случае, если в выборке и будут одинаковые результаты, то не более, чем число объединяемых запросов.
			SELECT DISTINCT age FROM teachers WHERE age < 25
			UNION ALL
			SELECT DISTINCT age FROM students WHERE age < 20;
		}
		
		//можно применять простые выражения
		SELECT name, salary, salary * 12 FROM teachers; // выведет кроме имени и зарплыты за месяц, годовую зарплату.
		
		// Можно назвать колонки по-своему
		SELECT name, salary AS month_salary, salary * 12 AS annual_salary FROM teachers;
		
		Функции {
			NOW() // возвращает текущее время
			DATEDIFF(first_date, second_date) // разость дат. первое минус второе.
			// Пример
			SELECT DATEDIFF(NOW(), registration_date) FROM students;
			
			IF(boolean, if_true, if_false) // уловный оператор
			// Пример
			SELECT name, IF(students_count > 500, 'Full', 'Not full') AS status FROM courses; // Будет создан дополнительный столбик status с результатами функции IF
			
			CONCAT(first, second, ..., last) // принимает нграниченное число парметров, склеивает строки
			
			// пример
			SELECT CONCAT('Зарплата у ', name, ' равна ', salary) FROM teachers;
			
			// COUNT()
			SELECT COUNT(*) FROM students;
			SELECT COUNT(name) FROM students; // будет анлогичным
			
			// AVG() - возвращает среднее
			// MAX() - возвращает максимальное значение поля
			// SUM() - сумма
		}
	
		JOIN/GROUP BY {
			SELECT table1.field, table2.field FROM table1
			JOIN table2 ON table1.id = table2.id /*после ON следует правило соединения таблиц*/
			<JOIN ON> /* можно делть несколько JOIN*/
			<WHERE><ORDER BY><LIMIT>; /* только после этого следуют остальные выражения*/
			
			По умолчанию все JOIN являются INNER JOIN - если есть строки, которым не нашлось соответствия во второй таблице, то строка не показывается в результате
			Есть также LEFT JOIN - если строке из левой (которая упоминается слева от JOIN) таблице нет соответствия, то она всё равно будет выведена в результат
			
			// GROUP группировка
			// следующий запрос позволит подсчитать количество взятых курсов у каджого студента. То есть сначала произойдет группировка по имени, а затем агрегирующая функция подсчитает количество строк.
			SELECT students.name AS Student, count(*) AS 'Courses count' FROM students
			JOIN subscription ON students.id = subscriptons.students_id
			GROUP BY name
			ORDER BY name;
		}
		
		Подзапросы {
			// Следующий запрос выдаёт для каждого студента количесвто учителей, которые их старше.
			SELECT name, (SELECT count(*) FROM teachers WHERE teachers.age > students.age) AS older_count FROM students ORDER BY older_count DESC LIMIT 5;
		}
	
	}
	
	DELETE {
		DELETE FROM table_name WHERE условие; // удаление одной сроки из таблицы
		Пример: DELETE FROM book WHERE id = 1;
	}
	
	INSERT/UPDATE {
	
		INSERT [INTO] имя_таблицы [(список_столбцов)] VALUES (значение1, значение2, ... значениеN);
		
		INSERT some_table values(value1, value2); // вставка во все имеющиеся поля
		
		INSERT some_table(field_name, field_name) VALUES(value1, value2); // вставка в конкретные поля
		
		INSERT some_table(field_name, field_name) VALUES(value1, value2), (value1, value2); // множественная всставка
		
		UPDATE courses SET price = price * 0.95 WHERE id = 46;
		
		// INSERT SELECT
		// Конструкция позволяет заполнить данными таблицу, результатом запроса.
		INSERT INTO table_name(field1, field2) SELECT ... // дальше идёт запрос.
		
	}
	
	// Other
	show variables like "character_set_database" // показывает текущую кодировку
	show variables like '%charac%'; // можно вести поиск по переменным по частичному названию
	
}