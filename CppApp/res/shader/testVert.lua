attribute = {"aPos", "aUV"}
verying = {"uv"}
uniform = {}

function main()
    -- print("aPos", aPos[1], aPos[2], aPos[3], aPos[4])
    -- print("aColor", aColor[1], aColor[2], aColor[3], aColor[4])
    -- print("aUV", aUV[1], aUV[2])
    cr_Position = aPos;
    cr_Position[4] = 1.0;
    cr_Position = cr.mul(projection, cr.mul(view, cr.mul(model, cr_Position)))
    uv = aUV;
end


