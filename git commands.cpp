Изучить{

	Сейчас {
		- Касательно ветвления
		
		- Попробовать ещё раз использовать git restore
			- Не понятно какой использовать параметр, если не коммит. Возникает ошибка: 
				error: pathspec '04409c9aaf3d692a549841086223b3f1cee4089a' did not match any file(s) known to git
			Попробовал использовать путь до файла, но ничего не произошло.
	}

	- Найти разницу
		git reset
		git revert
		git restore
		git show <commit>
	
	- git ls-files // показывает список файлов. Какие именно?
	- git ls-tree // не понятно что нужно подставлять на место <tree-ish>
}

Git commands {
	git init // создание репозитория
	git help
	git status
	git add { // добавление кода в индекс
		git add . // добавление всех файлов
		git add SomeFile.java // добавление конкретного файла
		git add -p AnotherFile.java // частичное добавление файла
	}
	git commit {
		git commit -m <название моего коммита> // добавление индекса в коммит
		git commit -a -m <назвние коммита> // добавление изменений в коммита минуя индекс
		git commit --amend // чтобы дополнить псследний коммит или поменять название
	}
	git rm <filename>// удаляет файл с диска
	git rm <filename> --cached // удаляет файл из трекинга?
	git mv <filename>// переименование файла
	git log // показ истории коммитов
	git show // показ последнего коммита
	git diff{ // сравнение коммитов
		git diff <commit1> <commit2> // коммиты выбираются а освное хеша коммита или расстояния от головы
		git diff <commit> // Хеш не подойдёт, только по ссылке на голову
		git diff HEAD~<колличетво коммитов назад, с которм сравниваем главный> // как указать коммит по количеству коммитов от головы
		git diff HEAD~1 /*Пример. сравнивает главный коммит (последний) и коммит отстоящий от него не единицу. Вмсто единицы может стоять другое число.
		В данно случа просто показываются изменения последнего коммита
		*/
		git diff HEAD~1 HEAD~2 // сравнивает 1 до головного коммит со 2 от головного
		git diff HEAD // покажет разницу между текущими изменениями и коммитом
		git diff SomeFile.java // проверить untracked изменения// чтобы проверить незакоммиченные и не добавленные в индекс изменения
		git diff --name-only <commit> // показать файлы, в которых что-то было изменено в указаном коммите
		git diff --name-only <commit1> <commit2> // показать файлы, в которых что-то было изменено между указанными коммиитами
		
		git diff <1 branch>..<2 branch> // сравнение веток
		// Примеры
		git diff master..dev
		git diff master..origin/master // origin - указание на то в каком именно репозитории смотрим измеения. До команды git fetch не имеет действия
		
		
		/*Дополнительно:
		- хеш можно указывать не полностью*/
	}
	git reset{
		// git reset применяетмя по умолчанию с параметром --mixed
		git reset HEAD <filename> // из индекса в unstaged
		git reset HEAD~<number> // назад на number число коммитов
		git reset <commit> // возврат к определённому коммиту, перенос всех последнующих коммитов в unstaged
		git reset --hard <commit>// откат к определённому коммиту и сброс последующей истории
		git reset --hard // откат к последнему коммиту, сброс незакоммиченных изменений.
		git reset --soft <commit> // возврат к определённому коммиту, а все послежующие изменения отправляются в индекс
		git reset --mixed HEAD <filename> // возврат к unstaged
	}
	git revert <commit> {
		// отмена изменений какого-то коммита, но сама запись о  коммите остаёются. Более того, требует совершить ещё один revert commit, чтобы закрепить коррективы.
	}
	git init // создание локального репозитория
	git clone <repositiry link> {
		// кодпирование удалённого репозитория к себе, создавая репозиторий с рабочей папкой. Важно то, в какой дирректории вы сейчак находитесь в консоли.
	}
	git push{ 
		// передача коммитов в центральнй репозиторий
		git push -u origin <destination branch name> // чтобы отправить в определённую ветку 
		/* Вариант с параметрами может быть нужен, когда в удалённом ропезитории ещё нет веток, например, при создании репозитория локально и передаче данных на сервер*/
		
		git push --delete origin <branch name> // удаление ветки в уделённом репозитории
	}	
	git pull { 
		git pull // вытягивание изменений с центрального репозитория в свою рабочую папку
		/* git pull is shorthand for git fetch followed by git merge FETCH_HEAD*/
		git fetsh
		git merge FETCH_HEAD
	}
	git checkout{
		git checkout -b <new branch name> // создание новой ветки
		git checkout <branch name> // переход в определённую ветку
		
		// Это что-то непонятное
		git checkout -- <filename> // отменить модификацию файлов
	}
	git remote{ 
		// shortname is often "origin"
		git remote // получение списка удалённых репозиториев
		git remote -v // получение адресов репозиториев
		git remote add <shortname> <url>
		git remote remove <shortname>
	}
	git branch{
		git branch -m <old name> <new name> // изменение имени ветки // m - modify
		git branch -l // получение списка веток // l - list
		git branch -d <branch name> // удаление ветки
		git push --delete origin <branch name> // удаление ветки в уделённом репозитории
	}
	git fetch {
		// вытягивает ветку из центрального репозитория, но не сливает изменения в локальный. git pull делает тоже самое, но ветки сразу сливает. git fetch позволяет получить ветку удалённого репозитория, чтобы, напрмиер, сравнить её с рабочей веткой
	}
	git merge{
		git merge -m <merge message>
		git merge <branch name> { // сливает указанную ветку в текущую ветку 
			intended to be used from master branch
			If I want to see changes commited in an another branch in the master branch,
			then I should use 
				git checkout master
				git merge another_branch
		}
		git merge --abort // отмена автоматического сливания, т.е. без конфликтов
		git merge FETCH_HEAD // слить fetch в локальныую master
		git merge FETCH_HEAD -m <merge message>// то же но дать название merge commit
	}
	git rebase <branch> {
		git rebase master // rebase current branch onto master
	}
	git cherry-pick <commit> // add a commit to current branch
	git blame <filename> //
	git gc // старых архивных версий
	git stash{
		git stash // застешить изменение, рабочая дирректория очищается от изменений
		git stash save <message> // то же самое, но дать сообщение стешу
		git stash save -m <message> // то же самое, но явно указываем ключ
		git stash -k // застешить изменение, но рабочая дирректория сохраняется
		git stash list // спискок стешей
		git stash pop ...// вытянуть стеш
		git stash clear // очистить все сташи
		git stash drop ...// очистить конкретный стеш
		git stash apply ...// применить стеш на дирректории, но сташ сохраняется в списке
		
		git stash show [<options>] [<stash>]
			git stash show -v <номер>
		
		
	}
	
	git config {
		git config --global core.editor "vim" 
		git config --global user.email "your_email_address@example.com" // логин
	}
	IDE features:
	stash // сохранить изменения, но не коммитить их
	annotate // git blame // узнать кто что писал. Кто какую строку
}
Bash commands {
	help // помощь
	cd	<path> // сменить текущую папку
	cd ../ //  или ..\ // чтобы вернуться в директорию на уровень выше. 
	cd ./../.. // Можно складывать
	ls // показать списко файлов и папок в текущем каталоге
	clear // очистить экран
	
}


Git tests{
	git pull and merging
		условия: remote branch tip is forward local branch
		То есть на remote есть новый коммит, которого нет локально
		
		1. на локальной ветке есть изменения, которых нет удалённо
			
			unstaged to commit
			/staged to commit (index)
			/commited
			
		
		2. все изменения 
			в одном файле
			/разных файлах
			
		Итого 6 ситуаций.
		Выводы:
			1. unstaged + same file
				error: Your local changes to the following files would be overwritten by merge:
					src/Some.java
				Please commit your changes or stash them before you merge.
				Aborting // no result
			2. staged + same file
				error: Your local changes to the following files would be overwritten by merge:
						src/Some.java
				Please commit your changes or stash them before you merge.
				Aborting // no result
			3. commited + same file
				Auto-merging src/Some.java
				CONFLICT (content): Merge conflict in src/Some.java
				Automatic merge failed; fix conflicts and then commit the result.
				
				/*I had to resolve merge conflict, right in the file, then add it to index and make a git commit
				At this point it would be ready to make a git push*/
				
			4. unstaged + different files
				Updating 6411497..4965a2a
				Fast-forward
				 NewFile.java | 10 ++++++++++
				 1 file changed, 10 insertions(+)
				 create mode 100644 NewFile.java

			5. staged + different files
				Updating 6411497..4965a2a
				Fast-forward
				 NewFile.java | 10 ++++++++++
				 1 file changed, 10 insertions(+)
				 create mode 100644 NewFile.java

			6. commiter + different files
				Merge made by the 'recursive' strategy.
				 NewFile.java | 10 ++++++++++
				 1 file changed, 10 insertions(+)
				 create mode 100644 NewFile.java

			/*
			I had just to give name to merge commit
			To give custom commit message, should used further commands
			*/
			git pull --edit // messaging via text redactor
			
			//or
			git fetch
			git merge FETCH_HEAD -m <merge message>	
}

