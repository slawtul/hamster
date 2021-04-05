# Hamster

Clipboard manager for Debian-based distributions - for elementary OS mostly

## Development

Before running app on you local machine, make sure you have *elementary-sdk* and *gtkmm-3.0* libs installed

```bash
sudo apt install elementary-sdk gtkmm-3.0 libxt-dev
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

You can mask with stars ****** passwords but remember if you chose _'Save list to file'_ in 'Preferences' window your
password will be save as __plain text__ in ~/.config/hamster/item.json file 
