# Übung 1 – Notizen zum RFC

Hier landen Entscheidungen und offene Fragen, bevor sie ins `RFC_Entwurf.docx` wandern.

## Vom Kick-off (30.10.2026)

- Aufgabe genau:
- Erwarteter Umfang (nur Kanäle setzen? Szenen, Überblenden, Blackout?):
- Hardware / Scheinwerfer im Labor:
- Sprache frei oder C++-Startprojekt Pflicht:
- Review in Übung 2 (andere Gruppe liest/implementiert unser RFC?):
- Termin Schlusspräsentation:

## Entscheidungen

| Datum | Entscheidung | Warum |
|---|---|---|
| | | |

## Leitfragen je Abschnitt der Vorlage

Die Antworten schreibt ihr selbst; die Fragen sollen nur zeigen, was jeder Abschnitt klären muss.

**Introduction** – Welches Problem löst das Protokoll, für wen, was ist ausdrücklich *nicht* Teil davon?

**Terminology** – Welche Begriffe brauchen eine feste Bedeutung (Kanal, Universum, Gerät/Fixture, Szene, Client, Server …)? Wie werden MUST/SHOULD/MAY verwendet (vgl. RFC 2119)?

**Communication Model**
- *System Overview* – Wer spricht mit wem, über welche Schicht (TCP, Port)? Skizze Client – Server – DMX-Interface.
- *Use Cases* – Was will ein Nutzer konkret tun können? Jeder Use Case braucht später einen Befehl.
- *Data Representation* – Text oder binär? Zeichensatz? **Wo endet eine Nachricht** (TCP ist ein Bytestrom!)? Wie werden Zahlen dargestellt, welche Wertebereiche?
- *Establishing Connection* – Wer verbindet sich, gibt es eine Begrüßung/Versionsabfrage, darf es mehrere Clients geben?
- *Error Recovery & Restart* – Was passiert bei Verbindungsabbruch, bei ungültigem Befehl, wenn das DMX-Interface fehlt? Welcher Zustand gilt nach einem Neustart?
- *Commands* – Welche Befehle, mit welchen Parametern?
- *Replies* – Antwortet der Server auf jeden Befehl? Welche Codes für Erfolg und welche Fehlerklassen (Muster: dreistellige Codes in RFC 765)?

**Declarative Specification**
- *Minimum Implementation* – Was muss jede Implementierung mindestens können?
- *Connection Handling*, *Commands & Replies* – Exakte Syntax, so dass jemand anderer nur nach dem Text programmieren kann.
- *Sequence* – Welche Reihenfolge ist erlaubt/verboten?
- *State Diagrams* – Zustände des Servers (bzw. der Verbindung) und Übergänge.

**Typical Scenarios** – Zwei bis drei komplette Abläufe Zeile für Zeile (Client sendet → Server antwortet), inklusive eines Fehlerfalls.
