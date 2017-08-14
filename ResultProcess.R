library("pracma")
setwd("~/Documents/GitHub/PolyFit---Evolutive-Algorithm")

list <- read.table("GAresults.txt")
for (i in 1:nrow(list))
{
  l <- read.table(toString(list$V1[i]), nrows = 1)
  t <- read.table(toString(list$V1[i]), skip = 1)
  
  x <- linspace(-10, 10, 100)
  
  y <- (x^0)*l[1,ncol(l)]
  for (j in (ncol(l)-1):2)
  {
    y <- y + (x^(ncol(l)-j))*l[,j]
  }
  yl <- x^3*list$V2[i] + x^2*list$V3[i] + x*list$V4[i] + list$V5[i]
  
  
  plot(t[-1,2],t[-1,3], xlim = c(-10,10), ylim = c(min(y)-1, max(y)+1), xlab = "", ylab = "")
  par(new = TRUE)
  plot(x, y, type = 'l', xlim = c(-10,10), ylim = c(min(y)-1, max(y)+1))
  par(new = TRUE)
  plot(x, yl, col = 'blue', type = 'l', xlim = c(-10,10), ylim = c(min(y)-1, max(y)+1), ylab = "")
  par(new = FALSE)
}