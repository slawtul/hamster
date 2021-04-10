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
sudo apt install meson gtkmm-3.0 libxt-dev wmctrl
```

## Building

```bash
cd hamster
meson build --prefix=/usr
cd build
ninja
ninja install
```

## Preferences

<p align="center">
    <img src="data/screenshots/github/prefs_win.png" alt="Screenshot">
</p>

|Name|Value|Description|
|---:|:---:|---|
|**Application**|||
|Run automatically on system startup|`true`||
|Run minimize|`false`||
|Set focus on a search input after pasting|`false`|Do you want to move cursor (focus) from text item list to search input after pasting?|
|Delay pasting [ms]|`320`|Maybe you have got a slow PC? This adjustment helps to set correct time value after minimizing a Hamster window and pasting text to destination window. <br>On my very old laptop from 2007, _Delay pasting_ set to less then `200` ms was problematic|
|**Text items**|||
|Eliminate leading and trailing spaces|`true`|Spaces, tabs, next line characters are removed from beginning and ending of a copied text.<br> Before: `\t\t    Hello hamster \n`<br>&nbsp;&nbsp;&nbsp;After:  `Hello hamster`|
|Save list to file|`true`|Next time when you open the app you will see previously copied text items - otherwise an empty list. <br>If `true` &nbsp;&nbsp;text items are saved in _'~ /.config/hamster/items.json'_ file <br>If `false` text items are kept in memory only|
|Item list size|`256`|How many text items do you want to keep in the app?|
|**Paste selected items with**|||
|Prefix|`empty`|No prefix by default|
|Suffix|`\n`|When you select text items and press `Enter` key, each of item is pasted in the new line.<br> This is a default behaviour every time you press `Enter` key, however you can evoke a prefix/suffix form with `Shift+Enter` key combination anytime before pasting|

## Shortcuts

<p align="center">
    <img src="data/screenshots/github/keys_win.png" alt="Screenshot">
</p>

## Open / Restore app with Elementary OS custom keybinding

![screenshot](data/screenshots/github/custom_keybinding.png)

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

### Special thanks to

* BobMorane (stackoverflow answer)
* Michi (stackoverflow answer)
* Vistaus (Dutch translation)

#### Donation via PayPal

[![screenshot](data/screenshots/github/pay-pal.png)](https://www.paypal.com/paypalme/slawtul)
