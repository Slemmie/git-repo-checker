# git-repo-checker
Recursively check for any local git repositories with untracked/uncomitted/unpushed local content. The stength lies in swiftly checking many independent repositories.

Motivaion: leaving the main work station (e.g. travel, etc.) - making sure all projects do not have untracked/unpushed content, which would render any attempt to continue work on said projects while away near-futile.

Note: Made in 10 minutes; limited completeness.

# Usage
```sh
$ make
```

Creates an executable `checker`, run with:

```sh
$ ./checker <root_dir>
```

Can accept more than one directory at a time.

The executable can be relocated, renamed, etc.
