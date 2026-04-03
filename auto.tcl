set nfacs [gtkwave::getNumFacs]

set toplist [list]

for {set i 0} {$i < $nfacs} {incr i} {
    set name [gtkwave::getFacName $i]
    set parts [split $name "."]

    if {[llength $parts] < 2} {
        continue
    }

    set topname [join [lrange $parts 0 1] "."]

    if {[lsearch -exact $toplist $topname] < 0} {
        lappend toplist $topname
    }
}

set toplist [lsort $toplist]

set num_added [gtkwave::addSignalsFromList $toplist]
puts "$num_added top level signals added"
