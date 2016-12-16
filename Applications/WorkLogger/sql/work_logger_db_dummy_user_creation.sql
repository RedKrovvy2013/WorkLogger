#do this after creating timer db, which is scripted in timer_db_creation.sql

DROP USER 'gmarius';

#add in your own pwd
CREATE USER 'gmarius'@'%' IDENTIFIED BY '';

GRANT ALL PRIVILEGES ON work_logger.* TO 'gmarius'@'%';

FLUSH PRIVILEGES;