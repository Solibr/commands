docker, создание контейнера
docker run --rm --name skill-mongo -p 127.0.0.1:27017:27017/tcp -d scalar4eg/skill-mongo-with-hacker
docker, обращение к клиенту командной строки
docker exec -it skill-mongo mongo

db.createCollection("students") // создание колекции в БД
db.students.insert({name:"Ivanov Ivan", age: "29"}) // добавление объекта
db.students.find() {// выводит все элементы
	db.students.find({name: "Ivan"}) // выводит объект с именем Ivan
	db.students.find({age: {$gt: "25"}}) // выводит объект, у которого age больше чем (Greater Than (gt)) 25
}
db.stduents.count() // выводит количество всех элементов в коллекции
db.students.find({name: "Ivan"}).count() // выводит количество объектов с именем Ivan

db.students.find({age: {$gt: "25"}}).sort({name: -1}) // фильтрация по возрасту и сортикровка по убыванию имени
db.students.find(...).sort(...).limit(5) // лимит результатов поиска. При значении 0 - отсутствие лимита

db.students.updateOne({name: "Ivan"},{$set: {age: "65"}}) // изменение одного из полей

