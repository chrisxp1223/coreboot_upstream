```{eval-rst}
:orphan:
```

# coreboot Release Process

This document describes our release process and all prerequisites to
implement it successfully.


## Purpose of coreboot releases
Our releases aren't primarily a vehicle for code that is stable across
all boards: The logistics of testing the more than 100 boards that are
spread out all continents (except Antarctica, probably) on a given tree
state are prohibitive for project of our size.

Instead, the releases are regular breakpoints that serve multiple
purposes: They support cooperation between multiple groups (corporations
or otherwise) in that it's easier to keep source trees synchronized
based on a limited set of commits. They allow a quick assessment of the
age of any given build or source tree based on its git version (4.8-1234
was merged into master a few months after 4.8, which came out in April
of 2018. 4.0-21718's age is harder to guess).

And finally we use releases to as points in time where we remove old
code: Once we decide that a certain part of coreboot gets in the way of
future development, we announce on the next release that we intend to
remove that part - and everything that depends on it - after the
following release. So removing feature FOO will be announced in release
X for release X+1. The first commit after X+1 is fair game for such
removal.

Together with our 3 months release horizon, this provides time to plan
any migrations necessary to keep older boards in the tree by bringing
them up to current standards.

## coreboot release team
To avoid issues of blocking the release on a single person, a release
team has been formed. Please see the `COREBOOT RELEASES` section of the
MAINTAINERS file for the current members.

These individuals work together to make sure releases are done on time,
follow the steps of this document, and update the release processes and
scripts.


## Needed credentials & authorizations

### coreboot admins only
* Website access is required to post the release files to the website.

### All release team members
* IRC topic access is required to update the topic.
* Git access rights are needed to post the tag.
* Blog post access is needed to do the blog post.
* A PGP key is required to sign the release tarballs and git tag.

Most of the steps in the release process can be done by anyone on the
release team. Only adding the files to the website needs to be done
by a coreboot administrator.

## When to release
Releases are done roughly on a 3-month schedule. If a release is
delayed, the next release will still be 3 months after the last release.


## Checklist

### ~6 weeks prior to release
- [ ] Announce upcoming release to mailing list, ask people to test and
      to update release notes.
- [ ] Start marking patches that should to go into the release with a
      tag "coreboot_release_X.yy".

### ~4 weeks prior to release
- [ ] Freeze toolchain state. Only relevant fixes are allowed from this point on.
- [ ] Schedule release meetings.

### ~2 weeks prior to release
- [ ] Meet with release team.
- [ ] Send reminder email to mailing list, ask for people to test, and to update the release notes.
- [ ] Update the topic in the IRC channel with the date of the upcoming release.

### ~1 week prior to release
- [ ] Meet with release team.
- [ ] Send reminder email to mailing list, ask for people to test,
      and to update the release notes.
- [ ] Update the topic in the IRC channel with the date of the upcoming
      release.
- [ ] If there are any deprecations announced for the following release,
      make sure that a list of currently affected boards and chipsets is
      part of the release notes.
- [ ] Finalize release notes as much as possible.
- [ ] Prepare release notes template for following release.
- [ ] Update `Documentation/releases/index.md.
- [ ] Check which branches need to be released. Any branch with changes
      should get a new release. Announce these branch releases and
      prepare release notes.

### Day before release tag
- [ ] Make sure patches with tags for the release are merged.
- [ ] Announce to IRC that the release will be tomorrow and ask for
      testing.
- [ ] Run `util/vboot_list/vboot_list.sh` script to update the list of
      boards supported by vboot.

### Day of release tag
- [ ] Meet with release team.
- [ ] Review the full documentation about doing the release below.
- [ ] Select a commit ID to base the release upon.
- [ ] Test the commit selected for release.
- [ ] Submit last pre-release release notes.
- [ ] Run the release script.
- [ ] Test the release from the actual release tarballs.
- [ ] Push signed Tag to repo. *This is the actual release step.*
      Once this patch is pushed, the release itself has been done.
      everything after this step is packaging and delivering the
      release.

- [ ] Announce that the release tag is done on IRC.
- [ ] Update the topic in the IRC channel that the release is done.

- [ ] Do the final release notes - Fill in the release date, remove
      "Upcoming release" and other filler from the current release
      notes.
- [ ] ADMIN: Upload release files to web server.
- [ ] ADMIN: Upload the final release notes to the web server.
- [ ] ADMIN: Upload crossgcc sources to web server.
- [ ] Create coreboot-sdk and coreboot-jenkins-node docker images
      based on the release ID and push them to dockerhub. These
      can be used as release builders.

### Week following the release
- [ ] Do the final release notes - Fill in the release date, remove "Upcoming release"
      and other filler from the current release notes.
- [ ] ADMIN: Upload release files & toolchain tarballs to the web server.
- [ ] ADMIN: Upload the final release notes to the web server.
- [ ] ADMIN: Upload crossgcc sources to the web server.
- [ ] Create coreboot-sdk and coreboot-jenkins-node docker images based on the release ID
      and push them to dockerhub. These can be used as release builders.
- [ ] Update download page to point to files, push to repo.
- [ ] Remove code that was announced it was going to be removed.
- [ ] Update AUTHORS file with any new authors.
- [ ] Update Documentation/releases/boards_supported_on_branches.md.

### 7 days after release tag
- [ ] Meet with release team.
- [ ] Write and publish blog post with release final notes. Branch releases notes (if any)
      should be included in the same post.
- [ ] Set up for next release.


### Creating a branch
- [ ] Branches are named 4.xx_branch to differentiate from the tags.
      Instructions on creating branches are listed below.


## Pre-Release tasks
Announce the upcoming release to the mailing list release 2 weeks ahead
of the planned release date.

The announcement should state the planned release date, point to the
release notes that are in the making and ask people to test the hardware
they have to make sure it's working with the current master branch,
from which the release will ultimately be derived from.

People should be encouraged to provide additions to the release notes.

The final release notes will reside in coreboot's Documentation/releases
directory, so asking for additions to that through the regular Gerrit
process works as well. Note that git requires lots of conflict
resolution on heavily edited text files though.

Frequently, we will want to wait until particular things are in the
release. Once those are in, you can select the commit ID that you want
to use for your release. For the 4.6 release, we waited until we had
time to do the release, then pulled in a few patches that we wanted
to have in the release. The release was based on the final of those
patches to be pulled in.

When a release candidate has been selected, announce the commit ID to
the #coreboot IRC channel, and request that it get some testing, just
to make sure that everything is sane.


## Generate the release
After the commit for the release has been selected and verified, run the
release script - util/release/build-release. This will download a new
tree, checkout the commit that you specified, download the submodules,
create a tag, then generate and sign the tarballs.

**Be prepared to type in your PGP key’s passphrase.**

```text
usage: util/release/build-release <version> [commit id] [username] [gpg key id]
Tags a new coreboot version and creates a tar archive

version:    New version name to tag the tree with
commit id:  check out this commit-id after cloning the coreboot tree
username:   clone the tree using ssh://USERNAME - defaults to https://
gpg key id: used to tag the version, and generate a gpg signature
```

After running the script, you should have a new directory for the
release, along with 4 files: 2 tarballs, and 2 signature files.

```text
drwxr-xr-x   9 martin martin      4096 Apr 30 19:57 coreboot-4.6
-rw-r--r--   1 martin martin  29156788 Apr 30 19:58 coreboot-4.6.tar.xz
-rw-r--r--   1 martin martin       836 Apr 30 19:58 coreboot-4.6.tar.xz.sig
-rw-r--r--   1 martin martin   5902076 Apr 30 19:58 coreboot-blobs-4.6.tar.xz
-rw-r--r--   1 martin martin       836 Apr 30 19:58 coreboot-blobs-4.6.tar.xz.sig
```

Here’s the command that was used to generate the 4.6 release:
```bash
util/release/build-release 4.6 db508565 Gaumless 3E4F7DF7
```


## Test the release from the tarballs
* Run “make what-jenkins-does” and verify that everything is building.
* Build and test qemu
```bash
cp configs/config.emulation_qemu_x86_i440fx .config
make olddefconfig
make
qemu-system-x86_64 -bios build/coreboot.rom -serial stdio
```
* Build and test any other platforms you can.
* Compare the directory from the tarballs to the coreboot repo to make
  sure nothing went wrong.
* Push the tag to git

A good tag will look like this:
````text
% git show 4.6
tag 4.6
Tagger: Martin Roth <martinroth@google.com>
Date:   Sun Apr 30 19:48:38 2017 -0600

coreboot version 4.6
-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1

iQIcBAABCQAGBQJZBpP2AAoJEBl5bCs+T333xfgQAKhilfDTzqlr3MLJC4VChbmr
...
678e0NzyWsyqU1Vx2rdFdLANx6hghH1R7E5ybzHHUQrhb55BoEsnQMU1oS0npnT4
dwfLho1afk0ZLPUU1JFW
=25y8
-----END PGP SIGNATURE-----

commit db508565d2483394b709654c57533e55eebace51 (HEAD, tag: 4.6, origin/master, origin/HEAD)
...
````

## Push the signed tag
When you used the script to generate the release, a signed tag was
generated in the tree that was downloaded. From the coreboot-X.Y tree,
just run: `git push origin X.Y`. In case you pushed the wrong tag
already, you have to force push the new one.

You will need write access for tags to the coreboot git repo to do this.


## After the release is tagged in git
Announce that the release has been tagged - this lets people know that
they should update their trees to grab the new tag. Until they do this,
the version number in build.h will still be based on the previous tag.

Copy the tarballs and .sig files generated by the script to
the coreboot server, and put them in the release directory at
`/srv/docker/www.coreboot.org-staticfiles/releases/`

````bash
# Update the sha256sum file
sha256sum -b coreboot-*.tar.xz > sha256suma.txt

# make sure the two new files are present (and nothing else has changed)
diff sha256sum.txt sha256suma.txt

mv sha256suma.txt sha256sum.txt
````

People can now see the release tarballs on the website at
<https://www.coreboot.org/releases/>

The downloads page is the official place to download the releases from,
and it needs to be updated with links to the new release tarballs and
.sig files. It can be found at:
<https://review.coreboot.org/cgit/homepage.git/tree/downloads.html>

Here is an example commit to change it:
<https://review.coreboot.org/c/homepage/+/19515>


## Upload crossgcc sources
Sometimes the source files for older revisions of
crossgcc disappear. To deal with that we maintain a mirror at
<https://www.coreboot.org/releases/crossgcc-sources/> where we host the
sources used by the crossgcc scripts that are part of coreboot releases.

Run

````bash
util/crossgcc/buildgcc -u
````

This will output the set of URLs that the script uses to download the
sources. Download them yourself and copy them into the crossgcc-sources
directory on the server.


## After the release is complete
Post the final release notes on <https://blogs.coreboot.org>


## Making a branch
At times we will need to create a branch, generally for patch fixes.
When making a branch, do NOT name it the same as the release tag: X.Y -
this creates trouble when trying to check it out, as git can’t tell
whether you want the tag or the branch. Instead, name it X.Y\_branch:
```bash
git checkout 4.8
git checkout -b 4.8_branch
git push origin 4.8_branch
```

You can then cherry-pick changes and push them up to the branch:
````bash
git cherry-pick c6d134988c856d0025153fb885045d995bc8c397
git push origin HEAD:refs/for/4.8_branch
````
