# -----------------------------------------------------------------------------
# Plan for batch edit of all files:
# 1. Do not update copyright date when do this edit
# 6. Convert tabs to spaces.
# 7. Change CPPAD_TESTVECTOR to a template type (see Eigen entry in wishlist).
# 9. Change Vector<T> -> <T>Vector for T = Base, Size, Bool (T != Set)
# 12. Remove all doxygen \a commands (not used consistently)
# 13. Remove CPPAD_INLINE_FRIEND_TEMPLATE_FUNCTION
# 14. Remove all inlines for functions that depend on template parameters.
# 17. Remove 'It returns true if it succeeds and false otherwise.'
# 18. Change template <class *> -> template <typename *>.
# 19. Create check_sort.sh and use it to sort all alphabetical lists.
# ----------------------------------------------------------------------------
# list of directories that are added to the repository by batch_edit.sh
# new_directories='
# '
# list of files that are deleted by batch_edit.sh
# delete_files='
# '
# list of files that are not edited by the sed commands in this file
# (with the possible exception of the extra_sed commands)
# ignore_files='
# '
# list of files and or directories that are moved to new names
# move_paths='
# '
# sed command that maps old file and or directory names to new file names
# move_sed='
# '
# list of files that get edited by the extra_sed command
# extra_files='
# '
# sed command that is applied to the extra files
# (after the other sed commands in this file)
# extra_sed='
# '
# ----------------------------------------------------------------------------
# Put other sed commands below here and without # at start of line
s|\\in B|\\in \\B{R}|g
s|\\times B|\\times \\B{R}|g
s|\\rightarrow B|\\rightarrow \\B{R}|g
s|B^|\\B{R}^|g
#
s|: B|: \\B{R}|g
s|"\([^"]*\): \\B{R}|"\1: B|