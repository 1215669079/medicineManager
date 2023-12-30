/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 50744
 Source Host           : localhost:3306
 Source Schema         : medicinemanager

 Target Server Type    : MySQL
 Target Server Version : 50744
 File Encoding         : 65001

 Date: 26/12/2023 17:22:41
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for agency
-- ----------------------------
DROP TABLE IF EXISTS `agency`;
CREATE TABLE `agency`  (
  `ano` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `aname` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `asex` char(1) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `aphone` char(12) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `apassword` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `aremark` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `manageauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `queryauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `browseauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `enterauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `deleteauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `alterauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `reportauth` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`ano`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of agency
-- ----------------------------
INSERT INTO `agency` VALUES ('1', 'agency', '男', '13100000000', 'agency', '', '有', '有', '有', '有', '有', '有', '有');
INSERT INTO `agency` VALUES ('2', 'agency1', '男', '13100000001', 'agency1', '', '有', '有', '有', '有', '有', '有', '有');
INSERT INTO `agency` VALUES ('3', 'zhan', '女', '13100000002', 'agency2', '', '无', '有', '有', '有', '有', '有', '有');
INSERT INTO `agency` VALUES ('4', 'liu', '男', '13100000003', 'liu', NULL, '无', '无', '有', '无', '无', '无', '无');

-- ----------------------------
-- Table structure for client
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client`  (
  `cno` int(10) NOT NULL AUTO_INCREMENT,
  `cname` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `csex` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cage` int(4) NULL DEFAULT NULL,
  `caddress` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cphone` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `csymptom` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mname` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `allergy` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `anamnesis` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cdate` datetime NULL DEFAULT NULL,
  `aname` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cremark` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`cno`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 12 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of client
-- ----------------------------
INSERT INTO `client` VALUES (1, '张三', '男', 12, '广东省广州市天河区上社街道', '13100000005', '倒萨大', '感冒灵颗粒*2;', '啊吴大维', '啊我的娃', '2023-12-12 23:01:00', 'agency', '达瓦达瓦');
INSERT INTO `client` VALUES (3, '王五', '男', 22, '广东省广州市天河区上社街道', '13100000005', '咳嗽', 'zhan', '无', '无', '2023-12-04 00:00:00', '止咳糖浆', '无');
INSERT INTO `client` VALUES (4, '李六', '男', 29, '广东省广州市天河区上社街道', '13100000005', 'adada', 'adada', 'adaddad1', 'adwadwd12', '2023-12-04 00:00:00', 'adadad', 'aadadaddada');
INSERT INTO `client` VALUES (6, '123', '男', 12, '广东省广州市天河区上社街道', '13100000005', '阿瓦达', '感冒灵颗粒*1;', '啊吴大维', '啊我的娃', '2023-12-12 13:24:00', 'agency', '达瓦达瓦');
INSERT INTO `client` VALUES (7, '张柳', '男', 12, '广东省广州市天河区上社街道', '13100000005', '阿瓦达', '感冒灵颗粒*1;', '啊吴大维', '啊我的娃', '2023-12-12 13:24:00', 'agency', '达瓦达瓦');
INSERT INTO `client` VALUES (8, '钮子', '男', 18, '广东省广州市天河区上社街道', '13100000005', '感冒', '感冒灵颗粒*1;', '啊吴大维', '啊我的娃', '2024-12-14 00:00:00', 'agency', '达瓦达瓦');
INSERT INTO `client` VALUES (11, '丫丫', '女', 22, '广东省广州市天河区岗顶街道', '13100000006', '感冒', '感冒灵颗粒*1;', '啊吴大维', '啊我的娃', '2024-12-14 00:00:00', 'agency', '达瓦达瓦');

-- ----------------------------
-- Table structure for medicine
-- ----------------------------
DROP TABLE IF EXISTS `medicine`;
CREATE TABLE `medicine`  (
  `mno` int(10) NOT NULL AUTO_INCREMENT,
  `mname` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mmode` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mefficacy` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `dosageform` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `type` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `specification` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `enterprise` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mprice` decimal(10, 2) NULL DEFAULT NULL,
  `inventory` int(4) NULL DEFAULT NULL,
  `mremark` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`mno`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 19 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of medicine
-- ----------------------------
INSERT INTO `medicine` VALUES (1, '感冒灵颗粒', '内服', '用于感冒引起的头痛，发热，鼻塞，流涕，咽痛等。', '颗粒型', 'OTC', '9*10g', '999', 10.00, 98, NULL);
INSERT INTO `medicine` VALUES (2, '感冒灵颗粒2', '内服', '用于感冒引起的头痛，发热，鼻塞，流涕，咽痛等。', '颗粒型', 'OTC', '9*10g', '999', 12.00, 99, NULL);
INSERT INTO `medicine` VALUES (3, '感冒灵颗粒3', '内服', '用于感冒引起的头痛，发热，鼻塞，流涕，咽痛等。', '颗粒型', 'OTC', '9*10g', '999', 14.00, 99, NULL);
INSERT INTO `medicine` VALUES (4, '阿莫西林', '内服', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (5, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (6, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (7, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (8, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (9, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (10, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (11, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (12, '%1', '内服', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (13, '%1', '内服', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (14, '%1', '内服', '%3', '%4', '%5', '%6', '%7', 88.00, 99, '%10');
INSERT INTO `medicine` VALUES (15, '%1', '%2', '%3', '%4', '%5', '%6', '%7', 14.00, 14, '%10');
INSERT INTO `medicine` VALUES (16, '达瓦', '外服', '阿瓦达', '达瓦', '中成药', '阿达', '挖的', 3.00, 4, '达瓦');
INSERT INTO `medicine` VALUES (17, '大王的', '外服', '大王的', '瓦达', '中成药', '阿瓦达', '挖地道', 3.00, 2, '达瓦');
INSERT INTO `medicine` VALUES (18, '感冒灵颗粒', '内服', '感冒', '瓦达', '中成药', '阿瓦达', '挖地道', 14.00, 88, '达瓦');

-- ----------------------------
-- Table structure for morder
-- ----------------------------
DROP TABLE IF EXISTS `morder`;
CREATE TABLE `morder`  (
  `ono` int(10) NOT NULL AUTO_INCREMENT,
  `cname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `csymptom` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mname` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `oamount` int(10) NULL DEFAULT NULL,
  `odate` datetime NULL DEFAULT NULL,
  `aname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `oremark` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`ono`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 9 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of morder
-- ----------------------------
INSERT INTO `morder` VALUES (1, '正确的', 'adsa', 'ads', 129, '2023-12-04 00:00:00', 'asd', 'ads');
INSERT INTO `morder` VALUES (2, '张三', '五', '感冒灵颗粒*1;', 10, '2000-01-01 01:33:00', 'agency', '五');
INSERT INTO `morder` VALUES (3, '张三', '撒打算水水', '感冒灵颗粒*1;感冒灵颗粒2*1;', 22, '2023-12-12 13:05:00', 'agency', '萨达');
INSERT INTO `morder` VALUES (6, '123', '阿瓦达', '感冒灵颗粒*1;', 10, '2023-12-12 13:24:00', 'agency', '阿瓦达');
INSERT INTO `morder` VALUES (7, '张柳', '阿瓦达', '感冒灵颗粒*1;', 10, '2023-12-12 13:24:00', 'agency', '阿瓦达');
INSERT INTO `morder` VALUES (8, '张三', '倒萨大', '感冒灵颗粒*2;', 20, '2023-12-12 23:01:00', 'agency', '订单');

-- ----------------------------
-- Table structure for purchase
-- ----------------------------
DROP TABLE IF EXISTS `purchase`;
CREATE TABLE `purchase`  (
  `pno` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mname` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `pdate` datetime NULL DEFAULT NULL,
  `poutdate` datetime NULL DEFAULT NULL,
  `aname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `premark` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`pno`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 4 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of purchase
-- ----------------------------
INSERT INTO `purchase` VALUES (1, '啦啦啦', '2023-12-04 00:00:00', '2023-12-04 00:00:00', '%4', '%5');
INSERT INTO `purchase` VALUES (2, '感冒灵颗粒*4;', '2023-12-12 18:17:00', '2024-12-12 18:17:00', 'agency', '大王的');
INSERT INTO `purchase` VALUES (3, '感冒灵颗粒*1;', '2023-12-12 22:58:00', '2024-12-12 22:58:00', 'agency', '达瓦');

SET FOREIGN_KEY_CHECKS = 1;
