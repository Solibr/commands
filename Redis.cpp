Установка и запуск через Docker {
	Установка и запуск контейнера через Docker
	docker run --rm --name skill-redis -p 127.0.0.1:6379:6379/tcp -d redis
	Получение доступа к клиентской консоли (Запуск)
	docker exec -it skill-redis redis-cli
}

// Комманды в действительноси могут содержать дополнительные параметы. В этой памятке их может не быть

SET someKey someValue // ОК // добавление значения по ключу
GET someKey // SomeValue // получение хранящегося значения по ключу
KEYS * // выводит список всех ключей
KEYS some* // выподит список всех ключей, соответствующих шаблону

DEL someKey // 1 // удаление элемента
DEL key [keys...]  { // <число удалённых элементов> // массовое удаление	
	DEL someKey1 someKey2 // 2 // для понимания синтаксиса - это перечисление
}

SADD key value [values...] {
	SADD key someValue1 someValue2 someValue3 ... // добавление уникального списка
}
SMEMBERS key // получение значений списка
SREM key value [values...] // удаление элементов их списка

ZADD key score member [score... member...] // member - хранящееся значение, score показатель для сортировки/
ZCARD key // количество элементов
ZCONT key min max {// Количество элементов в диапозоне
	ZCONT key -inf +inf // пример для получения количества всех элментов.
}
ZMSCORE key member // получить score у элемента
ZRANGE key min max BYSCORE [REV] [LIMIT offset count] // 
ZRANDMEMBER key // возвращает случайный элемент