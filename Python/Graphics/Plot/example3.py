from pylab import figure, rand, setp, show

contig_names = ['AAB0008r'] * 10
fig = figure()
ax = fig.add_subplot(111)
ax.plot(rand(10))
ax.set_xticks(range(10))
ax.set_xticklabels(contig_names)
setp(ax.get_xticklabels(), fontsize=10, rotation='vertical')
# fig.autofmt_xdate()
show()
