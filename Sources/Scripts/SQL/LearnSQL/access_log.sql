/*
 Navicat MySQL Data Transfer

 Source Server         : 127.0.0.1
 Source Server Version : 50621
 Source Host           : localhost
 Source Database       : RUNOOB

 Target Server Version : 50621
 File Encoding         : utf-8

 Date: 05/18/2016 14:15:39 PM
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `access_log`
-- ----------------------------
DROP TABLE IF EXISTS `access_log`;
CREATE TABLE `access_log` (
  `aid` int(11) NOT NULL AUTO_INCREMENT,
  `site_id` int(11) NOT NULL DEFAULT '0' COMMENT '网站id',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '访问次数',
  `date` date NOT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
--  Records of `access_log`
-- ----------------------------
BEGIN;
INSERT INTO `access_log` VALUES ('1', '1', '45', '2016-05-10'), ('2', '3', '100', '2016-05-13'), ('3', '1', '230', '2016-05-14'), ('4', '2', '10', '2016-05-14'), ('5', '5', '205', '2016-05-14'), ('6', '4', '13', '2016-05-15'), ('7', '3', '220', '2016-05-15'), ('8', '5', '545', '2016-05-16'), ('9', '3', '201', '2016-05-17');
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
