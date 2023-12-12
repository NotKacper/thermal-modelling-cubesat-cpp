thermalData <- read.csv("output50.000000.csv")

#Temperature <- matrix(
#  thermalData$temperature,
#  
#  nrow = length(Time),
#  ncol = length(BetaAngle),
#  byrow = TRUE
#)

# persp3D(x=Time, y=BetaAngle, z=Temperature, theta=120)

min(thermalData$temperature) - 273.15
max(thermalData$temperature) - 273.15

# Need to get Temperature readings into form A[i][j] = Temperature[time][beta_angle]

# figure <- plot_ly() %>% add_surface(x=~Time, y=~BetaAngle, z=~Temperature)

# figure