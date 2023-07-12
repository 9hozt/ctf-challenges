CREATE DATABASE IF NOT EXISTS checker_db;

use checker_db;

CREATE OR REPLACE USER 'user'@'%' IDENTIFIED BY 'user';

CREATE TABLE POS (
	POS_id INT NOT NULL AUTO_INCREMENT,
	serial_number VARCHAR(40),
	location VARCHAR(20),
	last_update TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY (POS_id)
);

CREATE TABLE cipher_keys (
	id INT NOT NULL AUTO_INCREMENT,
	cipher_key VARCHAR(100),
	PRIMARY KEY (id)
);

INSERT INTO POS(serial_number,location) VALUES('84da14d6-7325-11e9-a923-1681be663d3e','Bordeaux');
INSERT INTO POS(serial_number, location) VALUES('9f8f7014-7545-13ec-b127-1681be663d3e','Lille');
INSERT INTO POS(serial_number, location)  VALUES('e43c0780-5a62-43fe-b994-23496d9fa6c8','Lyon');


INSERT INTO cipher_keys(cipher_key) VALUES('PUTRANDOMKEYINHEREFORTHESIGNATURE');

GRANT ALL ON checker_db.* TO 'user'@'%';
GRANT FILE ON *.* TO 'user'@'%';

FLUSH PRIVILEGES;
