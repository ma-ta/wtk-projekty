-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Počítač: 127.0.0.1
-- Vytvořeno: Pát 22. led 2016, 22:14
-- Verze serveru: 10.1.9-MariaDB
-- Verze PHP: 7.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Databáze: `hrad`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `navstevnici`
--

CREATE TABLE `navstevnici` (
  `id` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `referer` varchar(1000) NOT NULL,
  `ip` varchar(50) NOT NULL,
  `os` varchar(50) NOT NULL,
  `browser` varchar(50) NOT NULL,
  `useragent` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabulky `zajemci`
--

CREATE TABLE `zajemci` (
  `ID` int(11) NOT NULL,
  `registrace` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `jmeno` varchar(200) NOT NULL,
  `email` varchar(200) NOT NULL,
  `telefon` varchar(18) NOT NULL,
  `profil` varchar(200) NOT NULL,
  `castka` int(11) NOT NULL,
  `zprava` text NOT NULL,
  `domena` varchar(200) NOT NULL,
  `souhlas` tinyint(1) NOT NULL DEFAULT '1',
  `referer` varchar(1000) NOT NULL,
  `ip` varchar(50) NOT NULL,
  `os` varchar(50) NOT NULL,
  `browser` varchar(50) NOT NULL,
  `useragent` varchar(200) NOT NULL,
  `heslo` char(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

--
-- Klíče pro exportované tabulky
--

--
-- Klíče pro tabulku `navstevnici`
--
ALTER TABLE `navstevnici`
  ADD PRIMARY KEY (`id`);

--
-- Klíče pro tabulku `zajemci`
--
ALTER TABLE `zajemci`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT pro tabulky
--

--
-- AUTO_INCREMENT pro tabulku `navstevnici`
--
ALTER TABLE `navstevnici`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pro tabulku `zajemci`
--
ALTER TABLE `zajemci`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
