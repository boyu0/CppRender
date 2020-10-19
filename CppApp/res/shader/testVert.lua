layout = {"aPos", "aColor"}
attribute = {
    aPos = {0, 0, 0, 1},
    aColor = {1, 1, 1, 1},
}
verying = {
    oColor = nil,
}
uniform = {
}

function main()
    print("aPos", aPos[1], aPos[2], aPos[3], aPos[4])
    cr_Position = aPos;
end
