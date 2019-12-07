-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- 主机： 10.53.228.19:13925
-- 生成日期： 2019-10-18 17:43:38
-- 服务器版本： 5.7.18-20170830-log
-- PHP 版本： 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 数据库： `DryClean`
--

-- --------------------------------------------------------

--
-- 表的结构 `corder`
--

CREATE TABLE `corder` (
  `cid` int(11) NOT NULL,
  `openid` text NOT NULL,
  `is_disinfection` int(11) NOT NULL,
  `is_incense` int(11) NOT NULL,
  `is_selfchoose` int(11) NOT NULL,
  `nation` text NOT NULL,
  `building` text NOT NULL,
  `room` text NOT NULL,
  `tel` text NOT NULL,
  `take_time` text NOT NULL,
  `price` int(11) NOT NULL,
  `s_iron` int(11) NOT NULL,
  `s_stain` int(11) NOT NULL,
  `s_seal` int(11) NOT NULL,
  `order_time` text NOT NULL,
  `status` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转储表的索引
--

--
-- 表的索引 `corder`
--
ALTER TABLE `corder`
  ADD PRIMARY KEY (`cid`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `corder`
--
ALTER TABLE `corder`
  MODIFY `cid` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
