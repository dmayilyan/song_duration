# Song Duration poking
Trying to find underlying distributions of song durations.

One can see a right skewed duration distribution that has a relatively clear pattern on the left side.
What was tried to fit:
- gauss + gauss
- gauss + poisson
- poisson + poisson
- other functions like gamma, exp, etc...

The latest approach includes finding an optimal fit of a poisson distribution targeting the left side of the distribution. Removal of the poisson from the data and expectation to see a combination of known distributions.
# Data
Data can be found in here [millionsongdataset.com](http://millionsongdataset.com/sites/default/files/AdditionalFiles/msd_summary_file.h5)
