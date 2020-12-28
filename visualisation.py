import pandas as pd
import cartopy
import cartopy.crs as ccrs
import matplotlib.pyplot as plt
import os

# Fiddle with figure settings here:
plt.rcParams['figure.figsize'] = (10,8)
plt.rcParams['font.size'] = 14
plt.rcParams['image.cmap'] = 'plasma'
plt.rcParams['axes.linewidth'] = 2

# Init map
cmap = plt.get_cmap('viridis')
ax = plt.subplot(111, projection=ccrs.PlateCarree())
ax.set_xlim([-20, 60])
ax.set_ylim([-40, 40])


start_location = os.getcwd()
reader = cartopy.io.shapereader.Reader('.\\color_map\\world_map\\World_Countries.shp')
countries_polygons = dict(enumerate(reader.geometries()))
africa_country_id = pd.read_csv(".\\color_map\\shp_id\\shp_id.csv")
answer = []
with open("answer.txt", "r") as f:
    answer = list(map(int, f.readline().split()))

colors = [10, 100, 200]
for i, country_id in enumerate(africa_country_id['shp_id']):
    ax.add_geometries([countries_polygons[country_id]], ccrs.PlateCarree(), facecolor=cmap(colors[answer[i] - 1]))

plt.savefig('visualization.png')
plt.show()
