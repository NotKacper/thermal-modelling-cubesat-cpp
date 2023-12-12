thermalData <- read.csv("ExtremeTempAgainstInputPower.csv")

plot(thermalData$Power.input..deg.C.,thermalData$Extreme.Temp..deg.C., xlab="Power heating due to inefficiency of batteries (W)", ylab="Extreme temperature achieved (C)", main="Extr. Temp. of model against input power")