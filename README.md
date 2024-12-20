# О программе
Данная программа предоставляет работу на C++ и подключение иных библиотек, отличных от базовых, это nlohmann_json (Работа с json файлами, подключено локально) и GTest (Воссоздание юнит тестов, подключено напрямую из GitHub)

Программа берет файл сначала Config.json, который должен находиться рядом с файлом запуска, проверяя основные требование в этом файле: "config"."name", "config"."version", "config"."max_responses", "files" (Массив, который хранит расположение файлов).

Потом requests.json, который хранит слова для поиска.

По окончанию программа создает answers.json, который хранит в себе результаты поискового движка, который ищет в файлах указанных в Config.json слова указанные в requests.json.

# Требование
Обязательно наличие возле .exe Config.json и requests.json.

Наличие файлов .txt по местоположению указанного в файлах Config.json.

# Прмеры JSON файлов
### Config.json
``` JSON 
{
    "config": {
        "name": "searchEngine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": [
        //массив местоположения файлов
    ]
}
```

### requests.json
``` JSON 
{
"requests": [
        //массив наборов слов для поиска(запросы)
    ]
}
```

### answers.json - результат программы
``` JSON 
{
    "answers": {
        "request001": {
            "result": "true",
            "relevance": {
                //массив нахождений совпадений в документах
            }
        },
        "request002": {
            "result": "true",
            //при одном совпадение не объявляется массив
        },
        "request003": {
            "result": "false"
        },
        "request(n)": {
            //кол-во requst зависит от количества запросов в requests.json
        }
    }
}
```

# Вывод в консоль
При некорректных входных данных, программа будет выводить информацию о ошибках и в каких файлах что-то не то.

Если все хорошо, то программа выводит информацию что движок запущен и в дальнейшем выводит информацию о выполненных действиях.

# Инструкция сборки
Для сборки программы, нужно использовать VS Code на Windows с предустановленной GCC и CMake.