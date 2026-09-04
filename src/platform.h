/*
 * D621-LVS
 *
 * Plattformweiche.
 *
 * Es gibt genau zwei unterstuetzte Zielplattformen:
 *
 *   PLATFORM_ESP32  - echtes Zielsystem, Ausgabe auf Hazeltine 2000A/B
 *                      ueber Hardware-UART + MAX3232, Arduino-Core.
 *   PLATFORM_LINUX  - Debug-Build (gcc), Ausgabe per ANSI-Escapecodes
 *                      auf der virtuellen Konsole.
 *
 * Die Erkennung erfolgt automatisch anhand des Compilers/SDKs, damit
 * derselbe Quellcode unveraendert in beiden Build-Systemen verwendet
 * werden kann (Makefile fuer Linux, PlatformIO fuer ESP32).
 */

#ifndef D621_PLATFORM_H
#define D621_PLATFORM_H

#if defined(ARDUINO) || defined(ESP32)
    #define PLATFORM_ESP32 1
#elif defined(__linux__)
    #define PLATFORM_LINUX 1
#else
    #error "Unbekannte Zielplattform - weder ARDUINO/ESP32 noch __linux__ definiert"
#endif

#endif
