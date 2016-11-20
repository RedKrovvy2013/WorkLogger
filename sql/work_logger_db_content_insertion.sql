
USE work_logger;

# good to list out fields to insert because without them, you must insert every
# field and do so in order shown by a CREATE TABLE statement

#dummy data with ids already matched between work_types/projects tables to tasks table
INSERT INTO `tasks` (`task_id`, `start_time`, `end_time`, `task_duration`, `work_type_id`, `project_id`, `description`) VALUES
	(46,'2015-10-23 10:59:34','2015-10-23 10:59:42','00:00:07',6,3,'Looked at some different restaurant websites.'),
	(47,'2015-10-23 11:02:31','2015-10-23 11:02:40','00:00:08',1,4,'Did prototype JSP pages for the planned web store checkout pages overhaul.'),
	(48,'2015-10-23 11:18:51','2015-10-23 11:18:58','00:00:07',2,3,'Testing that JCirone website works in different browsers.'),
	(49,'2015-10-23 11:20:11','2015-10-23 11:20:22','00:00:11',1,1,'Constructing GUI and animation art files for flash presentation.'),
	(50,'2015-10-23 11:24:39','2015-10-23 11:24:45','00:00:05',6,4,'Reviewed all web store CPs for their various flaws. There were many, many, many flaw. Oh so many.'),
	(51,'2015-10-23 11:28:28','2015-10-23 11:28:35','00:00:07',2,1,'Playing around with gui scrubber, play/pause btns.'),
	(52,'2015-10-23 11:29:14','2015-10-23 11:29:17','00:00:02',1,3,'Writing up Javascript sound from page-to-page code.'),
	(53,'2015-10-23 11:30:13','2015-10-23 11:30:20','00:00:06',2,4,'Making emulated purchases with new checkout pages.'),
	(54,'2015-10-23 11:31:30','2015-10-23 11:31:35','00:00:05',1,3,'Doing client change request; adding back-to-home page button.'),
	(55,'2015-10-23 14:39:25','2015-10-23 14:39:30','00:00:05',2,1,'Making last-second work-change removal of scene 24.');
	
#dummy data with ids already matched between work_types/projects tables to tasks table
INSERT INTO `work_types` (`work_type_id`, `work_type_title`, `is_active`, `is_deleted`) VALUES
(1,'Development','T', 'F'),
(2,'QA','T', 'F'),
(3,'ABCDEF','F', 'F'),
(4,'Personal','F', 'F'),
(5,'1234567','F', 'T'),
(6,'Research','T', 'T'),
(7,'Bug Resolution','T', 'F'),
(8,'Learning Time','F', 'T'),
(9,'Job Speculation','F', 'F'),
(10,'Organization','F', 'F');

#for starting fresh
-- INSERT INTO work_types (work_type_id, work_type_title, is_active) VALUES
-- 	(null, 'Development', 'T'),
-- 	(null, 'QA', 'T'),
-- 	(null, 'ABCDEF', 'F'),
-- 	(null, 'Personal', 'F'),
-- 	(null, '1234567', 'F'),
-- 	(null, 1, 'T'),
-- 	(null, 'Bug Resolution', 'T'),
-- 	(null, 'Learning Time', 'F'),
-- 	(null, 'Job Speculation', 'F'), 
-- 	(null, 'Organization', 'F');

#dummy data with ids already matched between work_types/projects tables to tasks table
INSERT INTO `projects` (`project_id`, `project_title`, `is_active`, `is_archived`, `start_date`, `is_deleted`) VALUES
(1,'Acme Mobility','T','F','2014-11-17', 'T'),
(2,'World Charity Website','F','F','2008-09-25', 'T'),
(3,'0018-Cuz\'s Website','T','F','2010-06-30', 'F'),
(4,'Checkout Pages Overhaul','T','F','2013-07-07', 'T'),
(5,'MCirone Flash Portfolio','F','T','2009-09-21', 'T'),
(6,'Eye Tracking Research Project','F','F','2005-05-14', 'F'),
(7,'FileDraven','F','F','2012-07-21', 'F'),
(8,'Acme Web-store A/B Testing','T','F','2015-03-21', 'F'),
(9,'MCirone Flash Portfolio','T','F','2015-02-01', 'F'),
(10,'0012 Bail Bonds Site','T','F','2012-05-17', 'F'),
(11,'Rhetoric Final Project','F','F','2003-04-05', 'T'),
(12,'Web Store Btns Standardization','F','F','2011-11-15', 'F'),
(13,'AeroNautilus Retainer Fall 2015','T','F','2015-09-21', 'F');

#for starting fresh
-- INSERT INTO projects (project_id, project_title, is_active, is_archived, start_date) VALUES
-- 	(null, 'Acme Mobility', 'T', 'F', '2014-11-17'),
-- 	(null, 'World Charity Website', 'F', 'F', '2008-09-25'),
-- 	(null, '0018-Cuz\'s Website', 'T', 'F', '2010-06-30'),
-- 	(null, 'Checkout Pages Overhaul', 'T', 'F', '2013-07-07'),
-- 	(null, 'MCirone Flash Portfolio', 'F', 'T', '2009-09-21'),
-- 	(null, 'Eye Tracking Research Project', 'F', 'F', '2005-05-14'),
-- 	(null, 'FileDraven', 'F', 'F', '2012-07-21'),
-- 	(null, 'Acme Web-store A/B Testing', 'T', 'F', '2015-03-21'),
-- 	(null, 'MCirone Flash Portfolio', 'T', 'F', '2015-02-01'),
-- 	(null, '0012 Bail Bonds Site', 'T', 'F', '2012-05-17'),
-- 	(null, 'Rhetoric Final Project', 'F', 'F', '2003-04-05'),
-- 	(null, 'Web Store Btns Standardization', 'F', 'F', '2011-11-15'),
-- 	(null, 'AeroNautilus Retainer Fall 2015', 'T', 'F', '2015-09-21');