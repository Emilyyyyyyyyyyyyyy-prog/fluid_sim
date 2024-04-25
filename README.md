# Diffusion simulation
Проект Симулятор диффузии

## Как собрать проект..

### на линуксе:

1. Вначале необходимо установить библиотеку SFML. Для этого воспользуйтесь командой `sudo apt-get install libsfml-dev`
2. В терминале перейдите в папку (для этого пропишите `cd <путь к папке>`), в которую хотите склонировать проект
3. Далее пишите: `git@github.com:Emilyyyyyyyyyyyyyy-prog/fluid_sim.git`
4. `cd fluid_sim`
5. Соберите проект с помощью уже готового Makefile. Для этого пропишите в терминале `make`
6. Для того, чтобы запустить проект введите в терминале `./sfml-app`
Готово, наслаждайтесь визуализацией физической модели диффузии!!!

### на винде:

Может, все-таки линукс????

Нет?! Ну так и быть( Для любителей помучаться можем предложить следующий вариант:

1. Скачайте **[Visual Studio](https://visualstudio.microsoft.com/ru/)**
2. Далее скачайте библиотеку **[SFML](https://www.sfml-dev.org/download.php)**
3. Теперь необходимо подключить SFML к VS. Вот отличная **[инструкция](https://www.youtube.com/watch?v=aSS7C85CYww)**
4. В терминале VS склонируйте этот репозиторий(команда из 3 пункта по установке на линукс)
Отлично, можете запускать!

## Фух, с установкой закончили, теперь давайте разберемся, куда тыкать

При запуске перед вами открывается меню: __start__, __settings__, __exit__. Нажимайте на кнопку __start__, тогда запустится симуляция с базовыми настройками. 

Если же вы хотите поэкспериментировать, то тыкайте на __settings__. Для вас открывается возможность поменять коэффициенты диффузии и вязкости газа. Нажмите на кнопку __save__, чтобы сохранить настройки. 

__Attention!__ Обращаем ваше внимание, что коэффициенты диффузии и вязкости принимают значения от 0 до 1, поэтому при неправильном вводе кнопка __save__ загорится красным(но если все корректно - зеленым). 

Нетрудно заметить боковое меню, при нажатие на которое выдвигагется кнопка __start__. Нажмите на нее, и тогда запустится симуляция с вашими настройками. Кнопка exit очевидно для выхода из приложения.

## Как оно рисует
- Вначале программа получает необходимые параметры
- При нажатии мыши(левая кнопка) появляется новый источник газа
- С помощью функций, которые более подробно описаны в видео, происходит красивое рассеивание газа в пространство
- При нажатии правой кнопки мыши можно очистить экран и заново любоваться диффузией
