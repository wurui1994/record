from pylab import figure,show,np

fig = figure()
ax = fig.add_subplot(111)


# plt.suptitle('Number of counts')
#
# ax.set_xlabel('x')
# ax.set_ylabel('y')
# ax.set_aspect('equal')

# I want max x axis to be 500
ax.set_xlim(0, 11)
# I want max y axis to be 300
ax.set_ylim(0, 11)

# I want major ticks to be every 20
major_ticks = np.arange(0, 13, 2)

# I want minor ticks to be every 5
minor_ticks = np.arange(0, 13, 1)
# If I do minor_ticks = np.arange(0, 301, 5), I will not get minor ticks for the entire plot


# Specify tick label size
ax.tick_params(axis='both', which='major', color='r', length=8, width=4)
ax.tick_params(axis='both', which='minor', color='b', length=6, width=2)
# Suppress minor tick labels

ax.set_xticks(major_ticks)
ax.set_xticks(minor_ticks, minor=True)
# ax.set_yticks(major_ticks)
# ax.set_yticks(minor_ticks, minor = True)

ax.set_xticklabels(range(2013, 2020), color='c')
for tick in ax.yaxis.get_majorticklabels():
    tick.set(color='b')

# Set both ticks to be outside
ax.tick_params(which='both', direction='out')


# Specify different settings for major and minor grids
# ax.grid(which = 'minor', alpha = 0.7)
ax.grid(which='major', axis='x', color='m')

ax.spines['bottom'].set_color('r')
ax.spines['top'].set_color('g')
ax.spines['right'].set_color('b')
ax.spines['left'].set_color('c')


# filename = 'C:\Users\Owl\Desktop\Plot.png'
# plt.savefig(filename, dpi = 150)
# plt.close()
show()
