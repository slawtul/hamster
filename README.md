# Hamster

Clipboard manager for Elementary OS

![screenshot](data/icons/128/com.github.slawtul.hamster.svg)

## Development

Before running app on you local machine, make sure you have installed below libs:

```bash
sudo apt install elementary-sdk gtkmm-3.0 libxt-dev wmctrl
```

## How to build

```bash
cd hamster
meson build --prefix=/usr
cd build
ninja
ninja install
```

### Known issues

#### 1. Pinned screenshot from Flameshot app

You cannot paste text if you took a screenshot and pinned to desktop

#### 2. About text item masking

You can mask passwords with stars ****** but remember if you chose _'Save list to file'_ in 'Preferences' window your
password will be save as __plain text__ in ~/.config/hamster/item.json file

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

### Screenshots

![screenshot](data/screenshots/wins.png)
