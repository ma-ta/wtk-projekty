-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Počítač: 127.0.0.1
-- Vytvořeno: Pát 10. kvě 2024, 08:00
-- Verze serveru: 10.4.32-MariaDB
-- Verze PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Databáze: `rpw`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `navstevnici`
--

CREATE TABLE `navstevnici` (
  `id` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT current_timestamp(),
  `referer` varchar(1000) NOT NULL,
  `ip` varchar(50) NOT NULL,
  `os` varchar(50) NOT NULL,
  `browser` varchar(50) NOT NULL,
  `useragent` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabulky `zajemci`
--

CREATE TABLE `zajemci` (
  `ID` int(11) NOT NULL,
  `registrace` timestamp NOT NULL DEFAULT current_timestamp(),
  `jmeno` varchar(200) NOT NULL,
  `email` varchar(200) NOT NULL,
  `telefon` varchar(18) NOT NULL,
  `profil` varchar(200) NOT NULL,
  `castka` int(11) NOT NULL,
  `zprava` text NOT NULL,
  `domena` varchar(200) NOT NULL,
  `souhlas` tinyint(1) NOT NULL DEFAULT 1,
  `referer` varchar(1000) NOT NULL,
  `ip` varchar(50) NOT NULL,
  `os` varchar(50) NOT NULL,
  `browser` varchar(50) NOT NULL,
  `useragent` varchar(200) NOT NULL,
  `heslo` char(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci ROW_FORMAT=COMPACT;

--
-- Indexy pro exportované tabulky
--

--
-- Indexy pro tabulku `navstevnici`
--
ALTER TABLE `navstevnici`
  ADD PRIMARY KEY (`id`);

--
-- Indexy pro tabulku `zajemci`
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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
