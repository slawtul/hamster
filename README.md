<p align="center">
    <img src="data/icons/128/com.github.slawtul.hamster.svg" alt="Icon" />
</p>

<h1 align="center">Hamster</h1>
<p align="center">Clipboard manager for Elementary OS</p>

<p align="center">
    <img width="482" height="682" src="data/screenshots/github/main_win.png" alt="Screenshot">
</p>

## Key features

* Select and paste multiple items at once
* Transform an item to uppercase or lowercase
* Mask an item with *******
* Paste selected items with prefix and suffix
* Save items to a file

## Development

Before building an app on you local machine, make sure you have installed below libs:

```bash
sudo apt install elementary-sdk gtkmm-3.0 libxt-dev wmctrl
```

## Building

```bash
cd hamster
meson build --prefix=/usr
cd build
ninja
ninja install
```

## Shortcuts

<p align="center">
    <img src="data/screenshots/github/keys_win.png" alt="Screenshot">
</p>

## Preferences

|Setting|Default|Description|
|---:|:---:|---|
|**Application**|||
|Run automatically on system startup|`true`||
|Run minimize|`false`||
|Set focus on a search input after pasting|`false`|You can choose if you want|
|Delay pasting [ms]|`320`|Maybe you have got a slow PC? This setting will help to set correct time value before minimizing a Hamster window and pasting text to destination window. <br>On my very old laptop from 2007, _delay pasting_ set to less then `200` ms was problematic|
|**Text items**|||
|Eliminate leading and trailing spaces|`true`|Spaces, tabs, next line characters will be removed before and after copied text|
|Save list to file|`true`|Next time when you open the app you will see previously copied text items - otherwise an empty list. <br>If `true` all text items are saved in _'~ /.config/hamster/items.json'_ file - when `false` - kept in memory only|
|Item list size|`256`|How many text items do you want to keep in the app?|
|**Paste selected items with**|||
|Prefix|`empty`||
|Suffix|`\n`||

<p align="center">
    <img src="data/screenshots/github/prefs_win.png" alt="Screenshot">
</p>

## Open / Restore app with Elementary OS custom keybinding

Inside `hamster/data` folder there is a `run_hamster.sh` file which you can bind to custom shortcut. I recommend a `ALT+V` key combination.

`run_hamster.sh` file **opens** an application or **restores** if minimized.
`run_hamster.sh` uses **wmctrl**

```bash
#!/bin/bash

wmctrl -l | awk '{$1=$2=$3="";print}' | grep "🐹 Hamster"

if [ $? -eq 0 ]; then
    wmctrl -a "🐹 Hamster"
    exit 1
else
    com.github.slawtul.hamster
    exit 0
fi
```

![screenshot](data/screenshots/github/custom_keybinding.png)

## Known issues

#### 1. Pinned screenshot from Flameshot app

You cannot paste text if you took a screenshot and pinned to desktop

#### 2. About text item masking

You can mask passwords with stars ****** but remember if you chose _'Save list to file'_ in _'Preferences'_ window your password will be saved as __plain text__ in ~/.config/hamster/item.json file

```json
{
  "items": [
    {
      "display_value": "A******3",
      "value": "Admin123"
    }
  ]
}
```
