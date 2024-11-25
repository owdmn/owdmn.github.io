
d <- read.csv("/home/ow/diss/raw_data/crossresolution/data/all-databases-mos-var.csv")
konx <- d[d$database=="KonX",]

konx <- konx[order(konx$VAR),]

print("HEAD")
print(head(konx[,c("filename", "VAR")]))
print("TAIL")
print(tail(konx[,c("filename", "VAR")]))
