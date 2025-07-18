# MSW

Extremely Lightweight
[Interception Tools](https://gitlab.com/interception/linux/tools) plugin to
prevent Mouse Wheel from sending false scroll events in opposite direction.

## Building

Pre-requisites:

- `git`
- `gcc`
- `make`
- Interception Tools

Run the following to build and install:

```bash
git clone https://github.com/Nafees10/msw.git
cd msw
make
strip msw
sudo cp msw /usr/local/bin/
```

## Configuration

The only thing that is meant to be changeable is the threshold time. You should
see a line in `msw.c` at top:

```c
#define THRESH_MS 20
```

Change 20 to milliseconds of threshold time.

## Setting It Up

Below is an example udevmon config (`/etc/interception/udevmon.yaml`):

```yaml
- JOB: "intercept -g $DEVNODE | msw | uinput -d $DEVNODE"
  DEVICE:
    EVENTS:
      EV_REL: [REL_WHEEL]
    NAME: ".*USB.*MOUSE.*"
```

After writing this file, execute the following as root:
```bash
sleep 2; systemctl restart udevmon.service
```

---

See also: [1806](https://github.com/Nafees10/1806)
See also: [dbt](https://github.com/Nafees10/dbt)
