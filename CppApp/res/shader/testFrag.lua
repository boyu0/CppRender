verying = {"oColor",}
uniform = {
}

function main()
    cr_Color = oColor;
    -- print(uv[1],uv[2])
    cr_Color = cr.texture2D(uv, texture);
    -- cr_Color = {uv[1], uv[2], 0, 1}
    -- print("cr_Color", cr_Color[1], cr_Color[2], cr_Color[3], cr_Color[4])
end

