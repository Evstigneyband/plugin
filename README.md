# WaveScope (AU + VST3)

Небольшой плагин-осциллоскоп: показывает форму волны входящего аудиосигнала в реальном времени.
Подходит для Logic Pro (формат **Audio Unit**) и для других DAW (формат **VST3**).

## Сборка (CMake + JUCE)

1) Установите [JUCE](https://juce.com). На macOS удобно через Homebrew:
   ```bash
   brew install juce
   ```
   Либо скачайте JUCE и укажите путь переменной `JUCE_DIR` (см. ниже).

2) Сгенерируйте проект Xcode и соберите:
   ```bash
   cd WaveScope
   cmake -B build -G Xcode -D CMAKE_OSX_ARCHITECTURES="arm64;x86_64" .
   cmake --build build --config Release
   ```

   Если CMake не находит JUCE, укажите путь вручную:
   ```bash
   cmake -B build -G Xcode -D JUCE_DIR=/path/to/JUCE/build -D CMAKE_OSX_ARCHITECTURES="arm64;x86_64" .
   ```

3) Где искать бинарники:
   - **AU (.component)**: `build/Release/WaveScope.component` (или внутри products Xcode).
   - **VST3**: `build/Release/WaveScope.vst3`.

4) Установка:
   - AU: скопируйте `.component` в `~/Library/Audio/Plug-Ins/Components/`
   - VST3: скопируйте `.vst3` в `~/Library/Audio/Plug-Ins/VST3/`

5) Проверка AU (опционально):
   ```bash
   auval -v aumu Wscp EVST
   ```

## Особенности
- Низкая задержка: данные из аудиопотока складываются в lock-free очередь и читаются GUI-потоком.
- Отрисовка 60 FPS по таймеру, антиалиасная линия, автоскейл по пику.
- Стерео-режим: левая и правая дорожки отрисовываются раздельно.

## Настройки/Расширения (идеи)
- Кнопка Freeze.
- Режим моно/стерео.
- Управление временем окна (0.05–1.0 c).
- Подложка под сетку, выбор цветовой схемы.

## Формат для Logic Pro
Logic Pro работает c **Audio Unit**. В проекте включены **AU** и **VST3**. Для Logic используйте цель AU.

Удачи!
