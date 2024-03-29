#!/usr/bin/env ruby
#
# Ruby script for generating Squash tarball releases
#
# Based on the work by:
# (c) 2005 Mark Kretschmann <markey@web.de>
# Some parts of this code taken from cvs2dist
# License: GNU General Public License V2


version  = `kdialog --inputbox "Enter Squash version: "`.chomp()

name     = "squash"
folder   = "#{name}-#{version}"

# Remove old folder, if exists
`rm -rf #{folder} 2> /dev/null`
`rm -rf #{folder}.tar.bz2 2> /dev/null`

Dir.mkdir( folder )
Dir.chdir( folder )

`svn co http://squash.googlecode.com/svn/trunk/ squash`

puts "\n"


# Remove SVN data folder
`find -name ".svn" | xargs rm -rf`
`mv squash/* .`
`rmdir squash`
`rm -rf qrc/svg 2> /dev/null`

# This stuff doesn't belong in the tarball
`rm -rf scripts`

puts "**** Compressing..  "
Dir.chdir( ".." ) # root folder
`tar -cf #{folder}.tar #{folder}`
`bzip2 #{folder}.tar`
`rm -rf #{folder}`
puts "done.\n"


puts "\n"
puts "========================================================"
puts "Congratulations :) Squash #{version} tarball generated.\n"
puts "\n"
puts "MD5 checksum: " + `md5sum #{folder}.tar.bz2`
puts "\n"
puts "\n"


