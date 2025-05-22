# get-dll-imports
Similar in functionality to my get-dll-exports, this gets all imports from a dll on disk. A good way to remember the difference is between imports and exports is, Imports pull dlls from the system, for example (api-ms-win-eventing-controller-l1-1-0.dll), and exports provide functions for userland to use like (RegSetValueA) in advapi32.dll

I made this while creating a larger framework I will be dropping soon called `snag`, because whats a hooks greatest enemy? A snag

-Sleepy
