Данная программа предоставляет работу на C++ и подключение иных библиотек, отличных от базовых, это nlohmann_json (Работа с json файлами, подключено локально) и GTest (Воссоздание юнит тестов, подключено напрямую из GitHub)

Программа берет файл сначала Config.json, который должен находиться рядом с файлом запуска, проверяя основные требование в этом файле: "config"."name", "config"."version", "config"."max_responses", "files" (Массив, который хранит расположение файлов).

Потом requests.json, который хранит слова для поиска.

По окончанию программа создает answers.json, который хранит в себе результаты поискового движка, который ищет в файлах указанных в Config.json слова указанные в requests.json.