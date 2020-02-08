# frozen_string_literal: true

# Shows top users
class LeaderboardsController < ApplicationController
  # All time top
  def index
    # TODO: could cache some leaderboards stuff
    @users = User.where.not(username: nil).where('points > 0').order(points: :desc)
    @top_users = @users.take(100)

    return if !user_signed_in? || @top_users.empty?

    @user_position = @users.index current_user

    if @user_position.nil?
      @user_position = 'none'
    else
      @user_position += 1
    end

    @points_to_go = @top_users.last.points - (current_user.points || 0)
  end
end
