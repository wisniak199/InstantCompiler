# InstantCompiler

Użyte biblioteki/narzędzia
llvm37 znajdujący się w katalogu /home/students/inf/PUBLIC/MRJP/llvm37/ na students
bnfc
jasmin

Struktura katalogów:
src/ - kod źródłowy kompilatora i skrypty bashowe
lib/parser - kod wygenerowany przez bnfc dla gramatyki z pliku lib/parser/Instant.cf
lib/jasmin - pliki jasmina

Użycie:
./insc_jvm <kompilowany plik>
./insc_llvm <kompilowany plik>

Szczegóły rozwiązania:
Po wygenerowaniu kodu z użyciem make pojawiają się 2 skrypty bashowe - insc_llvm oraz insc_jvm.
Są to kopie skryptów znajdujące się w src/insc_llvm.sh i src/insc_jvm.sh.
Skrypty te wywołują pliki binarne insc_llvm.bin i insc_jvm.bin w celu wygenerowania kodu w postaci tekstowej.
Następnie wywołują llvm-as/jasmin w celu wygenerowania pliku class/bitcode'u.

Do wygenerowania kodu llvm wykorzystana jest biblioteka llvm.
Kod generujący kod jasmin jest napisany "ręcznie". Wyrażenia wyliczane są w kolejności, która ogranicza zużycie stosu.
W obu przypadkach użyty jest wzorzec Visitor, którego schemat generuje bnfc.
