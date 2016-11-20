
CREATE DATABASE IF NOT EXISTS work_logger;

USE work_logger;

CREATE TABLE IF NOT EXISTS tasks
(
	task_id  INT  UNSIGNED  NOT NULL  AUTO_INCREMENT  PRIMARY KEY,
	start_time  DATETIME  NOT NULL,
	end_time  DATETIME  NOT NULL,
	task_duration  TIME  NOT NULL,
	work_type_id INT UNSIGNED NOT NULL,
	project_id INT UNSIGNED NOT NULL,
	description CHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS work_types
(
	work_type_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	work_type_title CHAR(25) NOT NULL,
	is_active CHAR(1) NOT NULL,
	is_deleted CHAR(1) NOT NULL
);

CREATE TABLE IF NOT EXISTS projects
(
	project_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	project_title CHAR(40) NOT NULL,
	is_active CHAR(1) NOT NULL,
	is_archived CHAR(1) NOT NULL,
	start_date DATE NOT NULL,
    is_deleted CHAR(1) NOT NULL
);