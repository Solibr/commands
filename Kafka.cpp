- На компе должна быть java минимум версии 8, иногда эта версия обозначается как 1.8


Запуск Zookeeper server {
	
	1. (необязательно) в папке config, в файле zookeeper.properties установить свойство
	dataDir=C:/kafka/zookeeper-data
	
	2. В консоли перейти в каталог с кафкой
	cd C:\kafka
	
	3. Запустить zookeeper следующей командой
	.\bin\windows\zookeeper-server-start.bat .\config\zookeeper.properties

}

Запуск Kafka server {
	
	1. (необязательно) в папке config, в файле server.properties установить свойство
	log.dirs=C:/kafka/kafka-logs

	2. Открыть консоль, перейти в каталог c кафкой
	cd C:\kafka
	
	3. Запустить Kafka следующей командой
	.\bin\windows\kafka-server-start.bat .\config\server.properties
}

Работа с консольными producer и consumer {
	перейти в C:\kafka\bin\windows
	
	Открыть Kafka producer
		kafka-console-producer.bat --bootstrap-server localhost:9092 --topic first
		
	Открыть Kafka consumer
		kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic first
		
	Открыть Kafka consumer и читать сначала (просто добавляется --from-beginning)
		kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic first --from-beginning

	Открыть Kafka consumer с group-name my-group (просто добавляется --group groupName)
		.\bin\windows\kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic first --group groupName
	
}


Запуск в Docker {	
	1. docker network create -d bridge kafka-net
	2. docker run -d --name zookeeper-server -p 2181:2181 --network kafka-net -e ALLOW_ANONYMOUS_LOGIN=yes bitnami/zookeeper:latest
	3. docker run -d --name kafka-server --network kafka-net -e ALLOW_PLAINTEXT_LISTENER=yes -e KAFKA_CFG_ZOOKEEPER_CONNECT=zookeeper-server:2181 -e KAFKA_CFG_ADVERTISED_LISTENERS=PLAINTEXT://localhost:9092 -p 9092:9092 bitnami/kafka:latest
	
	
	Другой способ:  (confluentinc/cp-kafka)
	1. Создать docker-compose.yml {
---
version: '3'
services:
  zookeeper:
    image: confluentinc/cp-zookeeper:7.3.0
    container_name: zookeeper
    environment:
      ZOOKEEPER_CLIENT_PORT: 2181
      ZOOKEEPER_TICK_TIME: 2000

  broker:
    image: confluentinc/cp-kafka:7.3.0
    container_name: broker
    ports:
    # To learn about configuring Kafka for access across networks see
    # https://www.confluent.io/blog/kafka-client-cannot-connect-to-broker-on-aws-on-docker-etc/
      - "9092:9092"
    depends_on:
      - zookeeper
    environment:
      KAFKA_BROKER_ID: 1
      KAFKA_ZOOKEEPER_CONNECT: 'zookeeper:2181'
      KAFKA_LISTENER_SECURITY_PROTOCOL_MAP: PLAINTEXT:PLAINTEXT,PLAINTEXT_INTERNAL:PLAINTEXT
      KAFKA_ADVERTISED_LISTENERS: PLAINTEXT://localhost:9092,PLAINTEXT_INTERNAL://broker:29092
      KAFKA_OFFSETS_TOPIC_REPLICATION_FACTOR: 1
      KAFKA_TRANSACTION_STATE_LOG_MIN_ISR: 1
      KAFKA_TRANSACTION_STATE_LOG_REPLICATION_FACTOR: 1
	}
	2. docker-compose up -d // в той же дирректории
	
		Базовый параметр --bootstrap-server localhost:9092
	
	kafka-console-consumer.sh { // прочитать из кафки
		Пример {
			kafka-console-consumer.sh --topic quickstart --bootstrap-server localhost:9092 --consumer-property auto.offset.reset=earliest
		}
		
		--topic topicName  // Чтение из топика
			--from-beginning { // Чтение с последнего коммита для этой группы. это короткая версия
				--consumer-property auto.offset.reset=earliest // это полная версия параметра
			}	
			--group groupName // указать группу явно. Если не указать, будет рандомная
	}
	kafka-console-producer.sh { // записать в кафку
		Пример  {
			kafka-console-producer.sh --bootstrap-server localhost:9092 --topic someName
		}
		
		--topic someName // указать топик
	}	
	kafka-topics.sh { // управление топиками
		Пример {
			// Создание топика
			kafka-topics.sh --bootstrap-server broker:9092 --create --topic topicName
		}
		
		
		Добавление топика. (Делать не обязательно) // При получении запроса на запись или чтение Kafka сама делает топик
		--create --topic topicName // создание топика
		--describe --topic topicName // описание топика
	}
	kafka-consumer-groups.sh { // управление группами
		Пример {
			kafka-consumer-groups.sh --bootstrap-server localhost:9092 --group groupName --describe
		}
		
		--group groupName --describe // Посмотреть описать групп консюмеров
		--group groupName --reset-offsest --to-earliest --topic topicName --execute // сбросить офсеты
	}


}