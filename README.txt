This is to note the difference between the QM preliminary version and the current version, and most importantly how to switch between them. The current version is the latest, and here's how to fall back to the QM prelim.
1. In  "ibu_fulldata.C", change the data_name from ".../New_Isobar_Hist/..." to ".../Isobar_Hist/..." for both lines 13 and 14.
2. In ~/isobar_hist_process/isobar_hist.h, switch back on the Sumw2()'s and Scale(0.5)'s in lines 47 thru 57.

Then you should be all set.
